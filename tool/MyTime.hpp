#pragma once

#include <chrono>
#include <string>

namespace time_ec
{
#define DURATION_CAST(unit) std::chrono::duration_cast<std::chrono::unit>

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

	class  time_compare
	{
		/**
		 * \brief
		 * \param interval 指定比较间隔,单位为秒
		 */
		time_compare(const int interval = 1)
			:m_begin_(std::chrono::system_clock::now())
		{
			m_interval_ = decltype(m_interval_)(interval);
		}

		/**
		* \brief
		* \param interval 指定比较间隔,单位为秒
		*/
		time_compare(const std::chrono::duration<int64_t> durat,
			const int interval = 1)
			:m_interval_(decltype(m_interval_)(interval)), m_begin_(durat)
		{
			//...
		}

		/**
		 * \brief 重设比较源
		 * \param other
		 */
		void reset(const std::chrono::time_point<std::chrono::system_clock> other)
		{
			m_begin_ = other;
		}

		/**		   间隔小于8小时有效(8*60*60s)
		 * \brief 判断两个时间点的数据是否在同一时间间隔内(间隔单位秒)
		 * \return
		 */

		bool is_same(const std::chrono::time_point<std::chrono::system_clock> other) const
		{
			const auto count_o = DURATION_CAST(seconds)(m_begin_.time_since_epoch()).count() / m_interval_;
			const auto count_s = DURATION_CAST(seconds)(other.time_since_epoch()).count() / m_interval_;
			return count_o == count_s;
		}

		/**
		 * \brief 传入unix时间戳,比较两个之间的差小于指定间隔
		 * \param other_second unix时间戳(单位秒)
		 * \return
		 */
		bool is_same(const int64_t other_second) const
		{
			const std::chrono::time_point<std::chrono::system_clock> other{
				std::chrono::duration<int64_t>(other_second) };
			return is_same(other);
		}

		/**
		 * \brief 传入 年月日  时分秒 比较
		 * \param ymd 年月日
		 * \param hms 时分秒
		 * \return
		 */
		bool is_same(const int ymd, const int hms) const
		{
			struct tm tm;
			memset(&tm, 0, sizeof(tm));
			//20180303
			tm.tm_year = ymd / 10000 - 1900;
			tm.tm_mon = (ymd % 10000) / 100 - 1;
			tm.tm_mday = ymd % 100;
			//95151
			tm.tm_hour = hms / 10000;
			tm.tm_min = (hms % 10000) / 100;
			tm.tm_sec = hms % 100;
			return is_same(static_cast<int64_t>(mktime(&tm)));
		}

	private:
		int														m_interval_;//间隔(秒)
		std::chrono::time_point<std::chrono::system_clock>		m_begin_;
	};

	class time_cast
	{

	private:

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
