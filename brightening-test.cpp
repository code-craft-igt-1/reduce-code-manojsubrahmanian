#include <gtest/gtest.h>
#include <memory>
#include "./brightener.h"

namespace brighteningtest {

TEST(BrighteningTest, BrightensWholeImage) {
    std::shared_ptr<Image> image = std::make_shared<Image>(2, 2);
    image->pixels[0] = 45; image->pixels[1] = 55;
    image->pixels[2] = 65; image->pixels[3] = 254;

    ImageBrightener brightener(image);
    int attenuatedCount = brightener.BrightenWholeImage();

    EXPECT_EQ(attenuatedCount, 1);         // Verify the number of attenuated pixels
    EXPECT_EQ(image->pixels[2], 90);      // Verify the expected brightened pixel value
}

TEST(BrighteningTest, BrightensWithAnotherImage) {
    std::shared_ptr<Image> image = std::make_shared<Image>(2, 2);
    image->pixels[0] = 45; image->pixels[1] = 55;
    image->pixels[2] = 65; image->pixels[3] = 75;

    ImageBrightener brightener(image);

    auto brighteningImage = std::make_shared<Image>(2, 2);
    brighteningImage->pixels[0] = 0; brighteningImage->pixels[1] = 25;
    brighteningImage->pixels[2] = 0; brighteningImage->pixels[3] = 25;

    int attenuatedCount = 0;
    bool succeeded = brightener.AddBrighteningImage(brighteningImage, attenuatedCount);

    EXPECT_TRUE(succeeded);               // Check if the operation succeeded
    EXPECT_EQ(image->pixels[0], 45);      // Verify the left-side pixel is unchanged
    EXPECT_EQ(image->pixels[1], 55);      // Verify the right-side pixel is brightened
    EXPECT_EQ(attenuatedCount, 0);        // Verify no pixels were attenuated
}

}  // namespace brighteningtest
