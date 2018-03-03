#pragma once

#include <chrono>
#include <string>

namespace time_ec
{
	class Timer
	{
	public:
		Timer() :m_begin(std::chrono::high_resolution_clock::now())
		{
			//...
		}
		//重置定时
		void reset()
		{
			m_begin = std::chrono::high_resolution_clock::now();
		}

		//默认输出毫秒
		int64_t elapsed() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}

		//默认输出秒,以double作为数字类型,可精确到小数
		double elapsed_second() const
		{
			return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}

		//微秒
		int64_t elapsed_micro() const
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}
		//输出分钟
		int64_t elapsed_minutes() const
		{
			return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}
		//输出小时
		int64_t elapsed_hours() const
		{
			return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}
		//纳秒
		int64_t elapsed_nano() const
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
	};

	class
	{

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
	};

	inline std::string getCurrentSystemTime()
	{
		auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
		struct tm ptm;
		localtime_s(&ptm, &tt);

		char date[60] = { 0 };
		sprintf_s(date, 60, "%d-%02d-%02d      %02d:%02d:%02d",
			static_cast<int>(ptm.tm_year) + 1900,
			static_cast<int>(ptm.tm_mon) + 1,
			static_cast<int>(ptm.tm_mday),
			static_cast<int>(ptm.tm_hour),
			static_cast<int>(ptm.tm_min),
			static_cast<int>(ptm.tm_sec));
		return std::string(date);
	}
}
