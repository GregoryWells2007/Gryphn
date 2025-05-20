typedef struct gnColor {
    union {
        struct {
            int r, g, b;
            float a;
        };

        struct {
            int red, green, blue;
            float alpha;
        };
    };

#ifdef GN_UTILS_CPP
    gnColor(int red, int green, int blue, float alpha = 1.0) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    gnColor(int color = 0, float alpha = 1.0) {
        this->red = color;
        this->green = color;
        this->blue = color;
        this->alpha = alpha;
    }
#endif
} gnColor;
