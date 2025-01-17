// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <memory>

#include "samples/console_progress.hpp"

/// @brief Responsible for progress bar handling within the benchmark_app
class ProgressBar {
public:
    explicit ProgressBar(size_t totalNum, bool streamOutput = false, bool progressEnabled = false) {
        _bar.reset(new ConsoleProgress(totalNum, streamOutput));
        _streamOutput = streamOutput;
        _isFinished = true;
        _progressEnabled = progressEnabled;
    }

    void add_progress(size_t num) {
        _isFinished = false;
        if (_progressEnabled) {
            _bar->addProgress(num);
        }
    }

    void finish(size_t num = 0) {
        if (num > 0) {
            add_progress(num);
        }
        _isFinished = true;
        if (_progressEnabled) {
            _bar->finish();
            std::cout << std::endl;
        }
    }

    void new_bar(size_t totalNum) {
        if (_isFinished) {
            _bar.reset(new ConsoleProgress(totalNum, _streamOutput));
        } else {
            throw std::logic_error("Cannot create a new bar. Current bar is still in progress");
        }
    }

private:
    std::unique_ptr<ConsoleProgress> _bar;
    bool _streamOutput;
    bool _isFinished;
    bool _progressEnabled;
};
