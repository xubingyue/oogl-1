//
// Created by xiaozhuai on 2018/12/17.
//
#ifndef OOGL_FPSCOUNTER_H
#define OOGL_FPSCOUNTER_H

#include <sys/time.h>
#include <functional>

namespace oogl {

class FPSCounter {
    public:
        explicit FPSCounter(long calcPerMillis = 1000) : mFps(0), mCalcPerMillis(calcPerMillis) {
            mLastTime = getCurrentTimeMillis();
        }

        inline void update() {
            long now = getCurrentTimeMillis();
            long spend = now - mLastTime;
            ++mFrameCount;

            if (spend > mCalcPerMillis) {
                mFps = (int) (1000 * mFrameCount / spend);
                mFrameCount = 0;
                mLastTime = now;
                mCallback(mFps);
            }
        }

        inline void setFpsChangedListener(const std::function<void(int)> &callback) {
            mCallback = callback;
        }

    protected:
        inline static long getCurrentTimeMillis() {
            struct timeval tv{0};
            gettimeofday(&tv, NULL);
            return tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }

        int mFps;
        long mLastTime;
        int mFrameCount = 0;
        std::function<void(int)> mCallback;
        long mCalcPerMillis;
};

}

#endif //OOGL_FPSCOUNTER_H
