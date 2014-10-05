#include <cmath>
#include <SGL/Core/SDL.hpp>
#include <SGL/System/StopWatch.hpp>

namespace {
    sgl::uint32 FpsStartTime = 0;
    sgl::uint32 NumFrames = 0;
    sgl::uint32 CurrentFps = 0;
}

namespace sgl {
    Time::Time(uint32 ms) {
        this->seconds = ms / 1000;
        while (this->seconds >= 60) {
            this->seconds -= 60;
            this->minutes++;
        }

        while (this->minutes >= 60) {
            this->minutes -= 60;
            this->hours++;
        }

        this->msecs = static_cast<uint16>(fmod(ms, 1000));
    }

    StopWatch::StopWatch() {
        this->reset();
    }

    void StopWatch::reset() {
        _startTime = DurationAsMs();
    }

    Time StopWatch::getElapsedTime() const {
        return Time(this->getElapsedMs());
    }

    uint32 StopWatch::getElapsedMs() const {
        return DurationAsMs() - _startTime;
    }

    /**
    * Returns the milliseconds since the application was started.
    */
    uint32 DurationAsMs() {
        return SDL_GetTicks();
    }

    /**
    * Returns the Time since the application was started.
    */
    Time DurationAsTime() {
        return Time(DurationAsMs());
    }

    /**
    * Wait for msecs milliseconds, which means that the application freeze for this time.
    */
    void WaitFor(uint32 msecs) {
        SDL_Delay(msecs);
    }

    /**
    * Returns the current framerate per second.
    */
    uint32 GetFPS(uint32* elapsedMs) {
        const uint32 elapsed_ms = DurationAsMs() - FpsStartTime;
        if (elapsedMs)
            *elapsedMs = elapsed_ms;

        if (elapsed_ms >= 1000) {
            CurrentFps = NumFrames;
            NumFrames = 0;
            FpsStartTime = DurationAsMs();
        }

        NumFrames++;

        return CurrentFps;
    }
}
