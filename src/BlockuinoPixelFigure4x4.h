#ifndef BLOCKUINO_PIXEL_FIGURE_4X4_H
#define BLOCKUINO_PIXEL_FIGURE_4X4_H

#include "BlockuinoPixelArcade.h"

/**
 * Concrete implementation of BlockuinoPixelFigure for a 2x2 figure.
 */
class BlockuinoPixelFigure4x4 : public BlockuinoPixelFigure {
private:
    uint32_t colors[16]; // 4x4 figure

public:
    /**
     * Constructor
     * @param colorsStr    Array of 4 hexadecimal color strings (e.g., {"#ff0000", "#00ff00", "#0000ff", "#ffff00"})
     * @param startIndex   The initial position index on the LED panel
     * @param panelSize    The size of the LED panel (panelSize x panelSize)
     */
    BlockuinoPixelFigure4x4(const String colorsStr[16], int startIndex, int panelSize);

    /**
     * Draw the 2x2 figure onto the NeoPixel strip.
     */
    void draw() override;

   /**
    * Check if a specific pixel is occupied.
    * @param pixelIndex Absolute index of the pixel on the panel.
    * @return true if the pixel is occupied (non-black), false otherwise.
    */
   bool isPixelOccupied(int pixelIndex) const override;
};

#endif // BLOCKUINO_PIXEL_FIGURE_2X2_H
