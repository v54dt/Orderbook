#include <benchmark/benchmark.h>

#include <cstring>
#include <iostream>

const char msg[] = {"\x38\x51\x92\x74\x61"};
const char str_msg[] = {"\x32\x33\x33\x30\x20\x20"};

template <typename T>
T DecodePackBcdToInt_1(const char* msg, int msg_len) {
  T output = 0;

  for (int idx = 0; idx < msg_len; idx++) {
    int second_digit = msg[idx] & 0x0f;
    int first_digit = (msg[idx] >> 4) & 0x0f;

    output = output * 100 + first_digit * 10 + second_digit;
  }
  return output;
}

template <typename T>
T DecodePackBcdToInt_2(const char* msg, int msg_len) {
  T output = 0;

  for (int idx = 0; idx < msg_len; idx++) {
    output = output * 100 + ((msg[idx] >> 4) & 0x0f) * 10 + (msg[idx] & 0x0f);
  }
  return output;
}

template <typename T>
T DecodePackBcdToInt_3(const char* msg, const int msg_len) {
  T output = 0;
  char* it = const_cast<char*>(msg);

  for (int idx = 0; idx < msg_len; idx++) {
    output = output * 100 + ((*it >> 4) & 0x0f) * 10 + (*it & 0x0f);
    it++;
  }
  return output;
}

template <typename T>
T DecodePackBcdToInt_4(const char* msg, const int msg_len) {
  T output = 0;
  char* it = const_cast<char*>(msg);

  for (int idx = 0; idx < msg_len; idx++) {
    output = output * 100 + (((*it) & 0x0f) >> 4) * 10 + (*it & 0x0f);
    it++;
  }
  return output;
}

template <typename T>
T DecodePackBcdToInt_5(const char* msg, const int msg_len) {
  T output = 0;
  char* it = const_cast<char*>(msg);
  int loop = msg_len;
  while (loop--) {
    output = output * 100 + ((*it >> 4) & 0x0f) * 10 + (*it & 0x0f);
    it++;
  }
  return output;
}

template <typename T>
T DecodePackBcdToInt_6(const char* msg, const int msg_len) {
  T output = 0;
  char* it = const_cast<char*>(msg);
  int loop = msg_len;
  while (loop--) {
    output = output * 100 + ((*it >> 4)) * 10 + (*it & 0x0f);
    it++;
  }
  return output;
}


static void BM_DecodePackBCD_1(benchmark::State& state) {
  for (auto _ : state) {
    int num = DecodePackBcdToInt_1<int>(msg, 4);
  }
}
BENCHMARK(BM_DecodePackBCD_1);

static void BM_DecodePackBCD_2(benchmark::State& state) {
  for (auto _ : state) {
    int num = DecodePackBcdToInt_2<int>(msg, 4);
  }
}
BENCHMARK(BM_DecodePackBCD_2);

static void BM_DecodePackBCD_3(benchmark::State& state) {
  for (auto _ : state) {
    int num = DecodePackBcdToInt_3<int>(msg, 4);
  }
}
BENCHMARK(BM_DecodePackBCD_3);

static void BM_DecodePackBCD_4(benchmark::State& state) {
  for (auto _ : state) {
    int num = DecodePackBcdToInt_4<int>(msg, 4);
  }
}
BENCHMARK(BM_DecodePackBCD_4);

static void BM_DecodePackBCD_5(benchmark::State& state) {
  for (auto _ : state) {
    int num = DecodePackBcdToInt_5<int>(msg, 4);
  }
}
BENCHMARK(BM_DecodePackBCD_5);

static void BM_DecodePackBCD_6(benchmark::State& state) {
  for (auto _ : state) {
    int num = DecodePackBcdToInt_6<int>(msg, 4);
  }
}
BENCHMARK(BM_DecodePackBCD_6);

BENCHMARK_MAIN();