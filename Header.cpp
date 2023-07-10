#include "Header.h"

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() == 0)
        return;
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

string svg_text(double left, double baseline, string text, int font_size) {
    return "<text x='" + to_string(left) + "' y='" + to_string(baseline) + "' font-size='" + to_string(font_size) + "'>" + text + "</text>" + '\n';
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='red' fill='#ffeeee'/>" << '\n';
}

void svg_end() {
    cout << "</svg>\n";
}
void show_histogram_svg(const vector<size_t>bins, int font_size) {
    const auto IMAGE_WIDTH = 1000;
    const auto IMAGE_HEIGHT = 500;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 20;
    const auto BINS_LIM = 80;

    int max_bin = bins[0];
    for (size_t bin : bins)
        if (bin > max_bin)
            max_bin = bin;
    bool scaling;
    if (max_bin > BINS_LIM)
        scaling = true;
    else
        scaling = false;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        double bin_width = BLOCK_WIDTH * bin;
        if (scaling)
            bin_width = BLOCK_WIDTH * bin / (max_bin / BINS_LIM);
        else
            bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), font_size);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
}
int get_font_size() {
    int font_size = 12;
    while (true) {
        cerr << "Enter font size (8-32): ";
        cin >> font_size;

        if (font_size >= 8 && font_size <= 32) {
            break;
        }
        else {
            cerr << "Invalid font size. Please enter a value between 8 and 32." << endl;
        }
    }
    return font_size;
}
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}