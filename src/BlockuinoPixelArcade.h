#ifndef BLOCKUINO_PIXEL_ARCADE_LIB_H
#define BLOCKUINO_PIXEL_ARCADE_LIB_H

#include "BlockuinoPixelFigure.h"
#include "BlockuinoPixelFigure1x1.h"
#include "BlockuinoPixelFigure2x2.h"
#include "BlockuinoPixelFigure3x3.h"
#include "BlockuinoPixelFigure4x4.h"

/**
 * Singleton class that provides utility functions and manages global settings
 * for the BlockuinoPixelArcade library.
 */
class PixelUtility {
public:
    /**
     * Retrieves the single instance of PixelUtility.
     * @return Reference to the PixelUtility instance.
     */
    static PixelUtility& getInstance();

    /**
     * Initializes the PixelUtility with an external NeoPixel strip.
     * Must be called before using other utility functions.
     * @param externalStrip Pointer to an existing Adafruit_NeoPixel instance.
     */
    void begin(Adafruit_NeoPixel* externalStrip);

    // Accessors and Mutators for global variables
    bool isAlternatingDirection() const;
    void setAlternatingDirection(bool state);

    bool isSwapDirections() const;
    void setSwapDirections(bool state);

    // Utility Functions
    int pixel_swap_directions(int pixel, int pixelWidth);
    int pixel_matrixPixel(int pixel);
    void pixel_clear();
    int pixel_moveRight(int position);
    int pixel_moveLeft(int position);
    int pixel_moveUp(int position);
    int pixel_moveDown(int position);
    uint32_t pixel_random_color();

    /**
     * Provides access to the NeoPixel strip.
     * @return Reference to the Adafruit_NeoPixel instance.
     */
    Adafruit_NeoPixel& getStrip();
    static uint32_t parseColor(const String& colorString);

private:
    // Private Constructor for Singleton Pattern
    PixelUtility();

    // Delete copy constructor and assignment operator to prevent copies
    PixelUtility(const PixelUtility&) = delete;
    PixelUtility& operator=(const PixelUtility&) = delete;

    // Pointer to the NeoPixel Strip
    Adafruit_NeoPixel* strip;

    // Global Variables
    bool strip_alternating_direction;
    bool strip_swap_horizontal_and_vertical_direction;
};

#endif