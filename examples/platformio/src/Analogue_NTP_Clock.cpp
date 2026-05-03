#if defined(ANALOGUE_NTP_CLOCK)

// Simple NTP clock example for UNIHIKER K10 using TFT_eSPI library
// Press Button A to toggle between analog and digital display
// Press Button B to change background color and play a tone sequence
// Adapted from: https://www.hackster.io/mircemk/making-a-retro-analog-ntp-clock-with-unihiker-k10-arduino-680e7a

#include <WiFi.h>
#include "time.h"     // Built-in for NTP handling
#include <TFT_eSPI.h> // TFT_eSPI library
#include <math.h>     // For sin/cos calculations
#include "unihiker_k10.h"

UNIHIKER_K10 k10;

uint8_t screen_dir = 2;
Music music;               // For button functionality
bool showAnalog = true;    // To track which display is showing
bool first_digital = true; // For digital display initialization

// Initialize display
TFT_eSPI tft = TFT_eSPI();

// Variables for digital display
int prev_hour = -1;
int prev_min = -1;
int prev_sec = -1;

uint16_t bgColors[] = {TFT_YELLOW, TFT_ORANGE, TFT_MAGENTA, TFT_OLIVE, TFT_WHITE};
int currentColorIndex = 0;
uint16_t currentBgColor = bgColors[0];

#define TFT_GREY 0x5AEB
#define TFT_LIGHTPINK 0xFDB8
#define TFT_GOLD 0xFEA0
#define TFT_LIGHTGREEN 0x9772
#define TFT_LIGHTSALMON 0xFD0F
#define TFT_ORANGE 0xFD20
#define TFT_MAGENTA 0xF81F
#define TFT_OLIVE 0x7BE0

// WiFi and NTP settings
const char *ssid = "Chez Thomas";
const char *password = "2625426254";
const char *ntpServer = "pool.ntp.org";
long gmtOffset_sec = 7 * -3600; // Timezone offset (UTC-7 for Mountain Time)
int daylightOffset_sec = 3600;  // Daylight Saving Time

// Clock parameters
const int center_x = 160;        // Center of display
const int center_y = 120;        // Center of display
const int x_radius = 110;        // Horizontal radius
const int y_radius = 90;         // Vertical radius
const int ellipse_offset_x = 3;  // Ellipse offset right
const int ellipse_offset_y = -2; // Ellipse offset up
const int second_length = 85;
const int minute_length = 70;
const int hour_length = 50;
const int center_size = 5;
const int tick_size = 3;

// Previous hand positions
int prev_sx = center_x, prev_sy = center_y;
int prev_m1x, prev_m1y, prev_m2x, prev_m2y, prev_m3x, prev_m3y;
int prev_h1x, prev_h1y, prev_h2x, prev_h2y, prev_h3x, prev_h3y;

// Flag for first loop
bool first_loop = true;

// Function prototypes
void onButtonAPressed();
void onButtonBPressed();
void drawDigitalClock(struct tm timeinfo);

// Function to calculate elliptical points with offset
void getEllipsePoint(float angle, float *x, float *y) {
    *x = center_x + ellipse_offset_x + x_radius * sin(angle);
    *y = center_y + ellipse_offset_y - y_radius * cos(angle);
}

void drawDigitalClock(struct tm timeinfo) {
    if (first_digital) {
        tft.fillScreen(currentBgColor);

        // Draw outer frame (5 pixels thick)
        tft.fillRect(0, 0, 320, 5, TFT_DARKGREY);
        tft.fillRect(0, 235, 320, 5, TFT_DARKGREY);
        tft.fillRect(0, 0, 5, 240, TFT_DARKGREY);
        tft.fillRect(315, 0, 5, 240, TFT_DARKGREY);

        // Draw inner frame (2 pixels thick)
        tft.drawRoundRect(8, 8, 304, 2, 20, TFT_BLACK);
        tft.drawRoundRect(8, 230, 304, 2, 20, TFT_BLACK);
        tft.drawRoundRect(8, 8, 2, 224, 20, TFT_BLACK);
        tft.drawRoundRect(310, 8, 2, 224, 20, TFT_BLACK);

        first_digital = false;
    }

    // Set text properties for time
    tft.setTextSize(4);                          // Size 4 for time
    tft.setTextColor(TFT_BLACK, currentBgColor); // Red text on yellow background

    int current_hour = timeinfo.tm_hour;
    int current_min = timeinfo.tm_min;
    int current_sec = timeinfo.tm_sec;

    // Position for the time display - centered
    int x = 40; // Adjusted for better centering
    int y = 80; // Adjusted vertical position

    // Update hours if changed
    if (current_hour != prev_hour) {
        char hourStr[3];
        sprintf(hourStr, "%02d", current_hour);
        tft.fillRect(x, y, 70, 45, currentBgColor); // Adjusted clear area
        tft.setCursor(x, y);
        tft.print(hourStr);
        prev_hour = current_hour;
    }

    // Always show colon
    tft.setCursor(x + 60, y);
    tft.print(":");

    // Update minutes if changed
    if (current_min != prev_min) {
        char minStr[3];
        sprintf(minStr, "%02d", current_min);
        tft.fillRect(x + 95, y, 70, 45, currentBgColor); // Adjusted clear area
        tft.setCursor(x + 95, y);
        tft.print(minStr);
        prev_min = current_min;
    }

    // Always show colon
    tft.setCursor(x + 155, y);
    tft.print(":");

    // Update seconds if changed
    if (current_sec != prev_sec) {
        char secStr[3];
        sprintf(secStr, "%02d", current_sec);
        tft.fillRect(x + 190, y, 70, 45, currentBgColor); // Adjusted clear area
        tft.setCursor(x + 190, y);
        tft.print(secStr);
        prev_sec = current_sec;
    }

    // Update date
    tft.setTextSize(3); // Size 3 for date
    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &timeinfo);

    // Center the date
    tft.fillRect(60, 150, 200, 30, currentBgColor); // Clear previous date
    tft.setCursor(65, 150);                         // Adjusted position for better centering
    tft.print(dateStr);
}

void onButtonAPressed() {
    showAnalog = !showAnalog;
    if (showAnalog) {
        // Instead of calling setup(), just redraw the analog clock
        tft.fillScreen(currentBgColor); // Use current background color

        // Draw frames
        tft.fillRect(0, 0, 320, 5, TFT_DARKGREY);
        tft.fillRect(0, 235, 320, 5, TFT_DARKGREY);
        tft.fillRect(0, 0, 5, 240, TFT_DARKGREY);
        tft.fillRect(315, 0, 5, 240, TFT_DARKGREY);

        tft.drawRoundRect(8, 8, 304, 2, 20, TFT_BLACK);
        tft.drawRoundRect(8, 230, 304, 2, 20, TFT_BLACK);
        tft.drawRoundRect(8, 8, 2, 224, 20, TFT_BLACK);
        tft.drawRoundRect(310, 8, 2, 224, 20, TFT_BLACK);

        // Draw clock face
        tft.setTextSize(2);
        for (int i = 0; i < 60; i++) {
            float ang_rad = i * 6.0 * PI / 180.0;
            float tx, ty;
            getEllipsePoint(ang_rad, &tx, &ty);

            if (i % 5 != 0) {
                tft.fillCircle(tx, ty, 1, TFT_DARKGREY);
            }
        }

        for (int i = 1; i <= 12; i++) {
            float ang_rad = i * 30.0 * PI / 180.0;
            float tx, ty;
            getEllipsePoint(ang_rad, &tx, &ty);

            if (i % 3 == 0) {
                char num[3];
                sprintf(num, "%d", i);
                int text_offset_x, text_offset_y;

                if (i == 12) {
                    text_offset_x = -12;
                    text_offset_y = -6;
                } else if (i == 3) {
                    text_offset_x = -4;
                    text_offset_y = -6;
                } else if (i == 6) {
                    text_offset_x = -6;
                    text_offset_y = -6;
                } else if (i == 9) {
                    text_offset_x = -6;
                    text_offset_y = -6;
                }

                tft.setCursor(tx + text_offset_x, ty + text_offset_y);
                tft.print(num);
            } else {
                tft.fillCircle(tx, ty, tick_size, TFT_BLACK);
            }
        }
        tft.fillCircle(center_x, center_y, center_size, TFT_BLACK);
        first_loop = true;
    } else {
        // Reset digital clock variables
        prev_hour = -1;
        prev_min = -1;
        prev_sec = -1;
        first_digital = true;
    }
}

void onButtonBPressed() {
    // Change background color
    currentColorIndex = (currentColorIndex + 1) % 5;
    currentBgColor = bgColors[currentColorIndex];

    // Play three-tone ascending sequence
    music.playTone(262, 200); // C4 (middle C)
    delay(250);               // Small delay between tones
    music.playTone(330, 200); // E4
    delay(250);
    music.playTone(392, 200); // G4

    // Redraw screen with new background color
    if (showAnalog) {
        onButtonAPressed(); // Redraw analog clock with new color
    } else {
        first_digital = true; // Force complete redraw of digital display
    }
}

void setup() {
    Serial.begin(115200);
    delay(3);
    Serial.println("\n\n\nAnalogue NTP Clock Example\n\n");

    k10.begin();
    k10.initScreen(screen_dir);

    // Add button callbacks
    k10.buttonA->setPressedCallback(onButtonAPressed);
    k10.buttonB->setPressedCallback(onButtonBPressed);

    // Initialize display
    tft.init();
    tft.setRotation(3); // Landscape mode
    tft.fillScreen(currentBgColor);
    tft.setTextColor(TFT_BLACK, currentBgColor);

    // Connect to WiFi
    tft.setCursor(30, 100);
    tft.setTextSize(3);
    tft.print("Connecting...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        tft.fillScreen(currentBgColor);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    tft.setCursor(55, 100);
    tft.setTextSize(3);
    tft.print("Connected!");
    delay(2000);
    tft.fillScreen(currentBgColor);

    // Draw outer frame (5 pixels thick)
    tft.fillRect(0, 0, 320, 5, TFT_DARKGREY);
    tft.fillRect(0, 235, 320, 5, TFT_DARKGREY);
    tft.fillRect(0, 0, 5, 240, TFT_DARKGREY);
    tft.fillRect(315, 0, 5, 240, TFT_DARKGREY);

    // Draw inner frame (2 pixels thick)
    tft.drawRoundRect(8, 8, 304, 2, 20, TFT_BLACK);
    tft.drawRoundRect(8, 230, 304, 2, 20, TFT_BLACK);
    tft.drawRoundRect(8, 8, 2, 224, 20, TFT_BLACK);
    tft.drawRoundRect(310, 8, 2, 224, 20, TFT_BLACK);

    // Initialize NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Draw static clock face
    tft.setTextSize(2);

    // First draw all second markers (60 small dots)
    for (int i = 0; i < 60; i++) {
        float ang_rad = i * 6.0 * PI / 180.0;
        float tx, ty;
        getEllipsePoint(ang_rad, &tx, &ty);

        if (i % 5 != 0) {
            tft.fillCircle(tx, ty, 1, TFT_DARKGREY);
        }
    }

    // Then draw hour markers over the second markers
    for (int i = 1; i <= 12; i++) {
        float ang_rad = i * 30.0 * PI / 180.0;
        float tx, ty;
        getEllipsePoint(ang_rad, &tx, &ty);

        if (i % 3 == 0) {
            char num[3];
            sprintf(num, "%d", i);
            int text_offset_x, text_offset_y;

            if (i == 12) {
                text_offset_x = -12;
                text_offset_y = -6;
            } else if (i == 3) {
                text_offset_x = -4;
                text_offset_y = -6;
            } else if (i == 6) {
                text_offset_x = -6;
                text_offset_y = -6;
            } else if (i == 9) {
                text_offset_x = -6;
                text_offset_y = -6;
            }

            tft.setCursor(tx + text_offset_x, ty + text_offset_y);
            tft.print(num);
        } else {
            tft.fillCircle(tx, ty, tick_size, TFT_BLACK);
        }
    }
    tft.fillCircle(center_x, center_y, center_size, TFT_BLACK);
}

void loop() {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        if (showAnalog) {
            int sec = timeinfo.tm_sec;
            int min = timeinfo.tm_min;
            int hour = timeinfo.tm_hour;

            // Clear previous hands if not first loop
            if (!first_loop) {
                tft.drawTriangle(prev_h1x, prev_h1y, prev_h2x, prev_h2y, prev_h3x, prev_h3y, currentBgColor);
                tft.drawTriangle(prev_m1x, prev_m1y, prev_m2x, prev_m2y, prev_m3x, prev_m3y, currentBgColor);
                tft.drawLine(center_x, center_y, prev_sx, prev_sy, currentBgColor);
            }

            // Store current text settings
            uint8_t current_size = tft.textsize;
            uint8_t current_font = tft.textfont;

            // Display date with its own settings
            tft.setTextSize(1);
            tft.setTextFont(2);
            char dateStr[11];
            strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &timeinfo);
            tft.setCursor(130, 150);
            tft.print(dateStr);

            // Restore original text settings
            tft.setTextSize(current_size);
            tft.setTextFont(current_font);

            // Calculate new hour hand position
            float h_deg = (hour % 12) * 30.0 + min * 0.5 + sec * (0.5 / 60.0);
            float h_rad = h_deg * PI / 180.0;
            int hx = center_x + hour_length * sin(h_rad);
            int hy = center_y - hour_length * cos(h_rad);
            float hdx = sin(h_rad);
            float hdy = -cos(h_rad);
            float hpx = -hdy;
            float hpy = hdx;
            float base_half = 5.0;
            int p1x = center_x + base_half * hpx;
            int p1y = center_y + base_half * hpy;
            int p2x = center_x - base_half * hpx;
            int p2y = center_y - base_half * hpy;
            int p3x = hx;
            int p3y = hy;

            // Draw hour hand with cyan fill and black outline
            tft.fillTriangle(p1x, p1y, p2x, p2y, p3x, p3y, TFT_CYAN);
            tft.drawTriangle(p1x, p1y, p2x, p2y, p3x, p3y, TFT_BLACK);

            // Calculate new minute hand position
            float m_deg = min * 6.0 + sec * 0.1;
            float m_rad = m_deg * PI / 180.0;
            int mx = center_x + minute_length * sin(m_rad);
            int my = center_y - minute_length * cos(m_rad);
            float dx = sin(m_rad);
            float dy = -cos(m_rad);
            float px = -dy;
            float py = dx;
            float m_base_half = 5.0;
            int m1x = center_x + m_base_half * px;
            int m1y = center_y + m_base_half * py;
            int m2x = center_x - m_base_half * px;
            int m2y = center_y - m_base_half * py;
            int m3x = mx;
            int m3y = my;

            // Draw minute hand (outlined)
            tft.drawTriangle(m1x, m1y, m2x, m2y, m3x, m3y, TFT_BLACK);

            // Calculate new second hand position
            float s_deg = sec * 6.0;
            float s_rad = s_deg * PI / 180.0;
            int sx = center_x + second_length * sin(s_rad);
            int sy = center_y - second_length * cos(s_rad);

            // Draw second hand
            tft.drawLine(center_x, center_y, sx, sy, TFT_RED);

            // Draw center dot
            tft.fillCircle(center_x, center_y, center_size, TFT_BLACK);

            // Update previous positions
            prev_h1x = p1x;
            prev_h1y = p1y;
            prev_h2x = p2x;
            prev_h2y = p2y;
            prev_h3x = p3x;
            prev_h3y = p3y;
            prev_m1x = m1x;
            prev_m1y = m1y;
            prev_m2x = m2x;
            prev_m2y = m2y;
            prev_m3x = m3x;
            prev_m3y = m3y;
            prev_sx = sx;
            prev_sy = sy;

            first_loop = false;
        } else {
            drawDigitalClock(timeinfo);
        }
    } else {
        Serial.println("Failed to obtain time");
    }
    delay(1000);
}
#endif
