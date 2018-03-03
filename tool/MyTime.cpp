#include <chrono>
#include <ctime>
#include <time.h>
#include <string>
#include <iostream>
#include <functional>
#include "MyTime.hpp"
#include <thread>

using namespace std;
using namespace chrono;

void test_time()
{
	std::cout << "++++++++++++++++++++++精度+++++++++++++++++++++" << endl;
	{//精度
		std::cout << "millisecond : ";
		std::cout << std::chrono::milliseconds::period::num << "/"
			<< std::chrono::milliseconds::period::den << "s" << std::endl;
	}
	std::cout << "++++++++++++++++++++时间段+++++++++++++++++++++" << endl;
	{
		std::chrono::milliseconds mscond(1000); // 1 second  
		std::cout << mscond.count() << " milliseconds.\n";

		std::cout << mscond.count() * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den;
		std::cout << " seconds.\n";
		//时间转换
		std::chrono::milliseconds ms(54802);
		std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
		cout << s.count() << endl;
	}
	std::cout << "++++++++++++++++++++时间点+++++++++++++++++++++" << endl;
	{
		/*
		template <class Clock, class Duration = typename Clock::duration>
		class time_point;
		std::chrono::time_point 表示一个具体时间，如上个世纪80年代、今天下午3点、火车出发时间等，
		只要它能用计算机时钟表示。
		第一个模板参数Clock用来指定所要使用的时钟（标准库中有三种时钟，system_clock，steady_clock
		和high_resolution_clock。见4时钟详解），第二个模板函数参数用来表示时间的计量单位
		(特化的std::chrono::duration<> )
		时间点都有一个时间戳，即时间原点。chrono库中采用的是Unix的时间戳1970年1月1日 00:00。
		所以time_point也就是距离时间戳(epoch)的时间长度（duration）。
		*/
		//距离时间戳2两秒   
		chrono::time_point<chrono::system_clock, chrono::seconds> tp(chrono::seconds(2));
		chrono::time_point<chrono::system_clock, chrono::seconds> tps(chrono::seconds(100000));
		cout << "to epoch : " << tp.time_since_epoch().count() << "s" << endl;
		cout << "to epoch : " << tps.time_since_epoch().count() << "s" << endl;
		//转化为ctime，打印输出时间点   
		time_t tt = chrono::system_clock::to_time_t(tp);
		char a[50];
		ctime_s(a, sizeof(a), &tt);
		cout << a;
	}
	std::cout << "++++++++++++++++++++时钟+++++++++++++++++++++" << endl;
	{
		cout << "system clock          : ";
		cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << "s" << endl;
		cout << "steady clock          : ";
		cout << chrono::steady_clock::period::num << "/" << chrono::steady_clock::period::den << "s" << endl;
		cout << "high resolution clock : ";
		cout << chrono::high_resolution_clock::period::num << "/" << chrono::high_resolution_clock::period::den << "s" << endl;
	}
	{
		//定义毫秒级别的时钟类型   
		typedef chrono::time_point<chrono::system_clock, chrono::milliseconds> microClock_type;
		//获取当前时间点，windows system_clock是100纳秒级别的(不同系统不一样，自己按照介绍的方法测试)，所以要转换   
		microClock_type tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
		//转换为ctime.用于打印显示时间   
		time_t tt = chrono::system_clock::to_time_t(tp);
		char _time[50];
		ctime_s(_time, sizeof(_time), &tt);
		cout << "now time is : " << _time;
		//计算距离1970-1-1,00:00的时间长度，因为当前时间点定义的精度为毫秒，所以输出的是毫秒   
		cout << "to 1970-1-1,00:00  " <<
			std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count()
			<< "ms" << endl;
	}
	{
		cout << time_ec::getCurrentSystemTime() << endl;
		time_ec::Timer  timer{};
		this_thread::sleep_for(chrono::seconds(10));
		cout << timer.elapsed_second() << endl;
		cout << timer.elapsed_micro() << endl;
		cout << timer.elapsed_nano() << endl;
	}
	std::cout << "\n\n" << endl;
	{
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		const function<void(const TimePoint&)> print_ms = [](const TimePoint& point)
		{
			using Ms = std::chrono::milliseconds;
			const Clock::duration since_epoch = point.time_since_epoch();
			std::cout << std::chrono::duration_cast<Ms>(since_epoch).count() << " ms\n";
		};

		const TimePoint default_value = TimePoint(); // (1)
		print_ms(default_value); // 0 ms

		const Clock::duration duration_4_seconds = std::chrono::seconds(4);
		const TimePoint time_point_4_seconds(duration_4_seconds); // (2)
																  // 从纪元开始 4 秒
		print_ms(time_point_4_seconds); // 4000 ms

		const time_point<steady_clock> time_point_now = Clock::now(); // (3)
		print_ms(time_point_now); // 43098276 ms

		const time_point<system_clock> time_point_sys = system_clock::now();
		const time_t tt = std::chrono::system_clock::to_time_t(time_point_sys);
		cout << "sys time :" << tt << endl;
		cout << "sys time :" <<
			duration_cast<std::chrono::microseconds>(time_point_sys.time_since_epoch()).count() << endl;
	}

}

// 制造函数工厂并使用它
#define FUNCTION(name, a) int fun_##name() { return a;}

FUNCTION(abcd, 12)
FUNCTION(fff, 2)
FUNCTION(qqq, 23)

#undef FUNCTION
#define FUNCTION 34
#define OUTPUT(a) std::cout << #a << '\n'

int main()
{

	{
		std::cout << "abcd: " << fun_abcd() << '\n';
		std::cout << "fff: " << fun_fff() << '\n';
		std::cout << "qqq: " << fun_qqq() << '\n';
		//std::cout << FUNCTION << '\n';
		OUTPUT(million);               // 注意缺少引号
	}
	system("pause");
	return 0;
}



int test_define()
{

	return 0;
}
