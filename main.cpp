#include <thread>
#include <chrono>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

int main() {
    constexpr double freq = 4000;
    const auto period = std::chrono::duration<double>(1.0/freq);
    const auto time_init = std::chrono::steady_clock::now();
    std::array<int64_t,50'000> jitter_array;
    std::array<int64_t,50'000> jitter_abs;
    std::array<int64_t,50'000> jitter_positive;

    for (int i = 0; i < 50'000; i++) {
        auto scheduled_time = time_init + i*period;
        std::this_thread::sleep_until(scheduled_time);
        auto actual_time = std::chrono::steady_clock::now();
        jitter_array[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(actual_time - scheduled_time).count();
    }
    int index = 0;
    for (auto i : jitter_array) {
        if (i>0)
            jitter_positive[index] = i;
        else
            jitter_positive[index] = 0;
        jitter_abs[index] = std::llabs(i);
        index++;
    }

    std::sort(jitter_array.begin(), jitter_array.end());
    int64_t p99 = std::ceil(0.99*50'000) - 1;
    int64_t p999 = std::ceil(0.999*50'000) - 1;
    const auto p99_value_ns =jitter_array[p99];
    const auto p999_value_ns =jitter_array[p999];
    const auto max_jitter_ns = jitter_array[49'999];

    std::cout << std::left
          << std::setw(8)  << "Freq"
          << std::setw(14) << "Period(ms)"
          << std::setw(12) << "p99(us)"
          << std::setw(14) << "p999(us)"
          << std::setw(12) << "Max(us)"
          << '\n';

    std::cout << std::string(60, '-') << '\n';

    std::cout << std::left
              << std::setw(8)  << freq
              << std::setw(14) << (period.count() * 1000.0)   // s -> ms
              << std::setw(12) << (p99_value_ns / 1000)        // ns -> us
              << std::setw(14) << (p999_value_ns / 1000)
              << std::setw(12) << (max_jitter_ns / 1000)
              << '\n';

    return 0;
}
