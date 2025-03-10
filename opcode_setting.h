#ifndef opcode_setting
#define opcode_setting

constexpr int kCategoryCount = 2;

constexpr int kNumCols = 96;
constexpr int kNumRows = 96;
constexpr int kNumChannels = 1;


constexpr int kMaxImageSize = kNumCols * kNumRows * kNumChannels;

constexpr int circle = 0;
constexpr int square = 1;
// constexpr char labels[] = {"circle","square"};
extern const char *kCategoryLabels[kCategoryCount];

#endif //opcode_setting
