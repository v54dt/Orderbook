std::string DecodeAsciiToString_1(const char* msg, const int msg_len) {
  char cp_msg[msg_len];
  memcpy(cp_msg, msg, msg_len);

  for (int idx = msg_len; idx > 0; idx--) {
    if (cp_msg[idx] != '\x20') {
      cp_msg[idx + 1] = '\x00';
      break;
    }
  }

  return std::string(cp_msg);
}

static void BM_DecodeAsciiToString_1(benchmark::State& state) {
  for (auto _ : state) {
    std::string symbol = DecodeAsciiToString_1(str_msg, 6);
  }
}
BENCHMARK(BM_DecodeAsciiToString_1);

std::string DecodeAsciiToString_2(const char* msg, const int msg_len) {
  int tmp;
  for (int idx = msg_len; idx > 0; idx--) {
    if (msg[idx] != '\x20') {
      tmp = idx;
    }
  }

  return std::string(msg, 0, tmp);
}

static void BM_DecodeAsciiToString_2(benchmark::State& state) {
  for (auto _ : state) {
    std::string symbol = DecodeAsciiToString_2(str_msg, 6);
  }
}
BENCHMARK(BM_DecodeAsciiToString_2);

std::string DecodeAsciiToString_3(const char* msg, const int msg_len) {
  char ret[msg_len + 1];
  bool find = false;
  int pos = 0;
  for (int i = msg_len - 1; i >= 0; i--) {
    if (find) {
      if (*msg != '\x20') {
        continue;
      } else {
        find = true;
        pos = i;
        *ret = *msg;
      }
    } else {
      *ret = *msg;
    }
  }
  ret[pos] = '\x00';
  return std::string(ret);
}

static void BM_DecodeAsciiToString_3(benchmark::State& state) {
  for (auto _ : state) {
    std::string symbol = DecodeAsciiToString_3(str_msg, 6);
  }
}
BENCHMARK(BM_DecodeAsciiToString_3);

BENCHMARK_MAIN();