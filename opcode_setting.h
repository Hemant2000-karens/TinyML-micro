#ifndef opcode_setting
#define opcode_setting

constexpr int kCategoryCount = 2;

constexpr int kNumCols = 224;
constexpr int kNumRows = 224;
constexpr int kNumChannels = 1;


constexpr int kMaxImageSize = kNumCols * kNumRows * kNumChannels;

constexpr int circle = 0;
constexpr int square = 1;
extern const char *kCategoryLabels[kCategoryCout];

#endif //opcode_setting
