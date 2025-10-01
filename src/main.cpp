#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <cstdint>
#include <optional>

#include "Point.h"
#include "ChaosGame.h"

struct InputData {
    std::uint64_t N{};   // кількість точок, які треба згенерувати
    Point start{};
    std::vector<Point> anchors;
};

static InputData read_input_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open input file: " + path);
    }

    InputData data{};
    if (!(in >> data.N)) {
        throw std::runtime_error("Invalid input: expected positive integer N.");
    }
    if (data.N == 0) {
        throw std::runtime_error("Invalid input: N must be > 0.");
    }

    if (!(in >> data.start.x >> data.start.y)) {
        throw std::runtime_error("Invalid input: expected initial point (x y).");
    }

    // Зчитуємо всі базові точки до EOF як пари (x y)
    double x, y;
    while (true) {
        // Спочатку пробуємо прочитати x
        if (!(in >> x)) {
            if (in.eof()) break;      // нормальне завершення
            throw std::runtime_error("Invalid input: malformed base points.");
        }
        // Потім y
        if (!(in >> y)) {
            throw std::runtime_error("Invalid input: base points must be pairs (x y).");
        }
        data.anchors.push_back({x, y});
    }

    if (data.anchors.empty()) {
        throw std::runtime_error("Invalid input: at least one base point is required.");
    }
    return data;
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3 || argc > 4) {
            std::cerr
                << "Usage:\n  " << argv[0]
                << " <input.txt> <output.txt> [seed]\n";
            return 2;
        }

        const std::string input_path  = argv[1];
        const std::string output_path = argv[2];
        std::optional<uint32_t> seed{};
        if (argc == 4) {
            try {
                unsigned long s = std::stoul(argv[3]);
                if (s > 0xFFFFFFFFul) throw std::out_of_range("seed too large");
                seed = static_cast<uint32_t>(s);
            } catch (const std::exception&) {
                throw std::runtime_error("Invalid seed: must be a non-negative integer ≤ 2^32-1.");
            }
        }

        const InputData data = read_input_file(input_path);

        // 1/2 до випадково обраної базової точки — класичні налаштування «хаос-гри»
        ChaosGameFunctor gen{data.start, data.anchors, 0.5, seed};

        std::ofstream out(output_path);
        if (!out) {
            throw std::runtime_error("Cannot open output file: " + output_path);
        }

        out.setf(std::ios::fixed);
        out << std::setprecision(10);

        for (std::uint64_t i = 0; i < data.N; ++i) {
            Point p = gen();               // наступна точка послідовності
            out << p.x << ' ' << p.y << '\n';
        }

        // Успіх
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
}