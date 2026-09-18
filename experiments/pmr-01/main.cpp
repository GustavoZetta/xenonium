#include <iostream>
#include <array>
#include <chrono>
#include <string>
#include <format>
#include <memory_resource>

std::string formatTime(std::chrono::nanoseconds ns) {
    double count = static_cast<double>(ns.count());

    if (count < 1'000.0) {
        return std::format("{:.2f}ns", count);
    } 
    else if (count < 1'000'000.0) {
        return std::format("{:.2f}us", count / 1'000.0);
    } 
    else if (count < 1'000'000'000.0) {
        return std::format("{:.2f}ms", count / 1'000'000.0);
    } 
    else {
        return std::format("{:.2f}s", count / 1'000'000'000.0);
    }
}

class Benchmark {
public:
    void Start() {
        End();
        m_benchmarking = true;
        m_lastTime = std::chrono::steady_clock::now();
    }

    void End() {
        if (!m_benchmarking) {
            return;
        }

        m_lastBenchmark = std::chrono::steady_clock::now() - m_lastTime;
        if (m_meansProcessed == 0) {
            m_lastMean = m_lastBenchmark;
        } else {
            m_lastMean = m_lastMean + (m_lastBenchmark - m_lastMean) / 2;
        }
        m_meansProcessed++;
    }

    void ClearMean() {
        End();
        m_lastMean = std::chrono::nanoseconds(0);
        m_meansProcessed = 0;
    }

    std::chrono::nanoseconds GetLastBenchmark() const {
        return m_lastBenchmark;
    }

    std::chrono::nanoseconds GetLastMean() const {
        return m_lastMean;
    }

    unsigned int GetIterated() const {
        return m_meansProcessed;
    }
private:
    bool m_benchmarking = false;

    std::chrono::steady_clock::time_point m_lastTime = std::chrono::steady_clock::now();
    std::chrono::nanoseconds m_lastBenchmark = std::chrono::nanoseconds(0);

    unsigned int m_meansProcessed = 0;
    std::chrono::nanoseconds m_lastMean = std::chrono::nanoseconds(0);
};


int main() {
    alignas(std::max_align_t) std::array<std::byte, 256> stack_buffer;
    std::pmr::monotonic_buffer_resource upstream(stack_buffer.data(), stack_buffer.size(), std::pmr::new_delete_resource());
    std::pmr::unsynchronized_pool_resource pool(&upstream);
    std::pmr::vector<int> numbers(&pool);

    Benchmark bench;

    for (int i = 0; i < 64; ++i) {    
        bench.Start();
        numbers.push_back(i * 10);
        bench.End();
        std::cout << "Added: " << numbers.back() << "; Time Elapsed: " << formatTime(bench.GetLastBenchmark()) << '\n';
    }
    std::cout << "Numbers processed: " << bench.GetIterated() << '\n';
    std::cout << "Mean: " << formatTime(bench.GetLastMean()) << '\n';

    bench.ClearMean();

    for (int i = 0; i < 1024; ++i) {    
        bench.Start();
        numbers.push_back(i * 10);
        bench.End();
        std::cout << "Added: " << numbers.back() << "; Time Elapsed: " << formatTime(bench.GetLastBenchmark()) << '\n';
    }
    std::cout << "Numbers processed: " << bench.GetIterated() << '\n';
    std::cout << "Mean: " << formatTime(bench.GetLastMean()) << '\n';
}
