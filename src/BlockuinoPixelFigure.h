#ifndef BLOCKUINO_PIXEL_FIGURE_H
#define BLOCKUINO_PIXEL_FIGURE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "BlockuinoPixelArcade.h"

/**
 * Abstract base class for NxN pixel figures.
 * Provides shared movement and collision detection functionalities.
 */
class BlockuinoPixelFigure {
public:
    virtual ~BlockuinoPixelFigure() {}

    // Movement functions
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void moveTo(int newPosition);
    bool doesHit(const BlockuinoPixelFigure &other);
    void setDirection(char newDirection);
    char getDirection();
    void rotateClockwise();
    void rotateCounterClockwise();
    /**
     * Pure virtual function to draw the figure.
     * Must be implemented by derived classes.
     */
    virtual void draw() = 0;

    /**
     * Pure virtual function to check if a specific pixel is occupied.
     * @param pixelIndex Absolute index of the pixel on the panel.
     * @return true if the pixel is occupied (non-black), false otherwise.
     */
    virtual bool isPixelOccupied(int pixelIndex) const = 0;

    /**
     * Get the current position of the figure.
     * @return The current position index.
     */
    int getPosition() const { return position; }
    /**
        * Get the row of the figure's top-left corner.
        * @return The row index.
    */
    int getRow() const { return position / panelSize; }
    /**
        * Get the column of the figure's top-left corner.
        * @return The column index.
    */
    int getColumn() const { return position % panelSize; }

protected:
    int panelSize;   // Size of the LED panel (e.g., 8 for an 8x8 panel)
    int figureSize;  // Size of the figure (1, 2, 3, or 4)
    int position;    // Top-left corner position in row-major index
    char direction = 'N';
    /**
     * Shared utility function to parse "#RRGGBB" strings into 32-bit NeoPixel colors.
     * Returns BLACK if the string is invalid or empty.
     */
    uint32_t parseHexColor(const String &hexColor) {
        // Check if the string starts with '#' and has exactly 7 characters
        if (hexColor.length() != 7 || hexColor[0] != '#') {
            return 0; // BLACK
        }

        // Extract substrings for R, G, B
        String rStr = hexColor.substring(1, 3);
        String gStr = hexColor.substring(3, 5);
        String bStr = hexColor.substring(5, 7);

        // Convert hex strings to integers
        long r = strtol(rStr.c_str(), NULL, 16);
        long g = strtol(gStr.c_str(), NULL, 16);
        long b = strtol(bStr.c_str(), NULL, 16);

        //Adafruit_NeoPixel& sharedStrip = PixelUtility::getInstance().getStrip();
        //return strip.Color(153, 0, 0);

        // Manually pack the color based on NEO_GRB format
        return ((g & 0xFF) << 16) | ((r & 0xFF) << 8) | (b & 0xFF);
    }
};

#endif // BLOCKUINO_PIXEL_FIGURE_H
