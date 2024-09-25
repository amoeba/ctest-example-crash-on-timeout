#include <execinfo.h>
#include <gtest/gtest.h>
#include <thread>

void signal_handler(int signum) {
  std::cerr << "Signal caught, about to crash. When ready, go check  "
               "~/Library/Logs/DiagnosticReports/"
            << std::endl;
  volatile int *p = nullptr;
  *p = 0;
}

TEST(SampleTest, TestTimeout) {
  // Start some threads that will just sleep so we can verify our crash log
  // shows all threads
  const int num_threads = 3;
  std::vector<std::thread> threads;

  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back([]() {
      std::this_thread::sleep_for(
          std::chrono::duration<int64_t, std::ratio<1>>(5)); // 5s
    });
  }

  // Join all threads
  for (auto &thread : threads) {
    thread.join();
  }
}

int main(int argc, char **argv) {
  // We catch SIGUSR1 which is sent from ctest, see signal_handler
  signal(SIGUSR1, signal_handler);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
