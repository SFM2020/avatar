#pragma once
#include <string>
#include <random>
#include <opencv2/core.hpp>

namespace ark {
    namespace util {
        /**
        * Splits a string into components based on a delimiter
        * @param string_in string to split
        * @param delimiters c_str of delimiters to split at
        * @param ignore_empty if true, ignores empty strings
        * @param trim if true, trims whitespaces from each string after splitting
        * @return vector of string components
        */
        std::vector<std::string> split(const std::string & string_in,
            char const * delimiters = " ", bool ignore_empty = false, bool trim = false);

        /**
        * Splits a string into components based on a delimiter
        * @param string_in string to split
        * @param delimiters c_str of delimiters to split at
        * @param ignore_empty if true, ignores empty strings
        * @param trim if true, trims whitespaces from each string after splitting
        * @return vector of string components
        */
        std::vector<std::string> split(const char * string_in, char const * delimiters = " ",
            bool ignore_empty = false, bool trim = false);

        /** Trims whitespaces (space, newline, etc.) in-place from the left end of the string */
        void ltrim(std::string & s);

        /** Trims whitespaces (space, newline, etc.) in-place from the right end of the string */
        void rtrim(std::string & s);

        /** Trims whitespaces (space, newline, etc.) in-place from both ends of the string */
        void trim(std::string & s);

        /** Convert a string to upper case in-place */
        void upper(std::string & s);

        /** Convert a string to lower case in-place */
        void lower(std::string & s);

        std::string resolveRootPath(const std::string & root_path);

        /**
        * Get the color at index 'index' of the built-in palette
        * Used to map integers to colors.
        * @param color_index index of color
        * @param bgr if true, color is returned in BGR order instead of RGB (default true)
        * @return color in Vec3b format
        */
        cv::Vec3b paletteColor(int color_index, bool bgr = true);
    }

    // Randomization utilities
    namespace random_util {
        template<class T>
        /** xorshift-based PRNG */
        inline T randint(T lo, T hi) {
            if (hi <= lo) return lo;
            static unsigned long x = std::random_device{}(), y = std::random_device{}(), z = std::random_device{}();
            unsigned long t;
            x ^= x << 16;
            x ^= x >> 5;
            x ^= x << 1;
            t = x;
            x = y;
            y = z;
            z = t ^ x ^ y;
            return z % (hi - lo + 1) + lo;
        }

        /** Uniform distribution */
        float uniform(float min_inc = 0., float max_exc = 1.);

        /** Gaussian distribution */
        float randn(float mean = 0, float variance = 1);
    } // random_util
}