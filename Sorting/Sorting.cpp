#include "pch.h"
#include <iostream>
#include <string>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "BubbleSort.h"
#include "InsertionSorter.h"
#include "QuickSorter.h"
#include "HeapSorter.h"
#include "Timer.h"


#define DO(inst) std::printf("\n" #inst "\n"); inst

TEST_CASE("Test Bubble Sort", "[Sorting]")
{
#if BUBBLE_IMPLEMENTED

	{
		std::cout << "Test Bubble Sort 10" << std::endl;
		Sorting::BubbleSorter bubbles(10);

		Timer time;
		time.start();

		bubbles.Sort();

		time.stop();

		REQUIRE(bubbles.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Bubble Sort 100" << std::endl;
		Sorting::BubbleSorter bubbles(100);

		Timer time;
		time.start();

		bubbles.Sort();

		time.stop();

		REQUIRE(bubbles.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Bubble Sort 1 000" << std::endl;
		Sorting::BubbleSorter bubbles(1000);

		Timer time;
		time.start();

		bubbles.Sort();

		time.stop();

		REQUIRE(bubbles.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Bubble Sort 10 000" << std::endl;
		Sorting::BubbleSorter bubbles(10000);

		Timer time;
		time.start();

		bubbles.Sort();

		time.stop();

		REQUIRE(bubbles.IsSorted());
		std::cout << std::endl;
	}

	/*{
		std::cout << "Test Bubble Sort 100 000" << std::endl;
		Sorting::BubbleSorter bubbles(100000);

		Timer time;
		time.start();

		bubbles.Sort();

		time.stop();

		REQUIRE(bubbles.IsSorted());
		std::cout << std::endl;
	}*/


	//BENCHMARK_ADVANCED("Bubbles 10")(Catch::Benchmark::Chronometer meter) {
	//	Sorting::BubbleSorter bubbles(10);

	//	meter.measure([&bubbles] { return bubbles.Sort(); });

	//	REQUIRE(bubbles.IsSorted());
	//};

	//BENCHMARK_ADVANCED("Bubbles 100")(Catch::Benchmark::Chronometer meter) {
	//	//Timer time;
	//	//time.start();

	//	Sorting::BubbleSorter bubbles(100);

	//	meter.measure([&bubbles] { return bubbles.Sort(); });

	//	REQUIRE(bubbles.IsSorted());

	//	//time.stop();
	//};

	//BENCHMARK_ADVANCED("Bubbles 1000")(Catch::Benchmark::Chronometer meter) {
	//	//Timer time;
	//	//time.start();

	//	Sorting::BubbleSorter bubbles(1000);

	//	meter.measure([&bubbles] { return bubbles.Sort(); });

	//	REQUIRE(bubbles.IsSorted());

	//	//time.stop();
	//};

	//BENCHMARK_ADVANCED("Bubbles 10000")(Catch::Benchmark::Chronometer meter) {
	//	//Timer time;
	//	//time.start();

	//	Sorting::BubbleSorter bubbles(10000);

	//	meter.measure([&bubbles] { return bubbles.Sort(); });

	//	REQUIRE(bubbles.IsSorted());

	//	//time.stop();
	//};

	// 100k tests are really long, uncomment if you want to transform your CPU into a hot machine !
	//BENCHMARK_ADVANCED("Bubbles 100000")(Catch::Benchmark::Chronometer meter) {
	//	Sorting::BubbleSorter bubbles(100000);

	//	meter.measure([&bubbles] { return bubbles.Sort(); });
	//};
#else
	FAIL("Bubble sort unimplemented");

#endif
}

TEST_CASE("Test Insertion Sort", "[Sorting]")
{
#if INSERTION_IMPLEMENTED
	
	{
		std::cout << "Test Insertion Sort 10" << std::endl;
		Sorting::InsertionSorter insertion(10);

		Timer time;
		time.start();

		insertion.Sort();

		time.stop();

		REQUIRE(insertion.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Insertion Sort 100" << std::endl;
		Sorting::InsertionSorter insertion(100);

		Timer time;
		time.start();

		insertion.Sort();

		time.stop();

		REQUIRE(insertion.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Insertion Sort 1 000" << std::endl;
		Sorting::InsertionSorter insertion(1000);

		Timer time;
		time.start();

		insertion.Sort();

		time.stop();

		REQUIRE(insertion.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Insertion Sort 10 000" << std::endl;
		Sorting::InsertionSorter insertion(10000);

		Timer time;
		time.start();

		insertion.Sort();

		time.stop();

		REQUIRE(insertion.IsSorted());
		std::cout << std::endl;
	}

	/*{
		std::cout << "Test Insertion Sort 100 000" << std::endl;
		Sorting::InsertionSorter insertion(100000);

		Timer time;
		time.start();

		insertion.Sort();

		time.stop();

		REQUIRE(insertion.IsSorted());
		std::cout << std::endl;
	}*/

	/*BENCHMARK_ADVANCED("Insertion 10")(Catch::Benchmark::Chronometer meter) {
		Sorting::InsertionSorter insertion(10);

		meter.measure([&insertion] { return insertion.Sort(); });

		REQUIRE(insertion.IsSorted());
	};

	BENCHMARK_ADVANCED("Insertion 100")(Catch::Benchmark::Chronometer meter) {
		Sorting::InsertionSorter insertion(100);

		meter.measure([&insertion] { return insertion.Sort(); });

		REQUIRE(insertion.IsSorted());
	};

	BENCHMARK_ADVANCED("Insertion 1000")(Catch::Benchmark::Chronometer meter) {
		Sorting::InsertionSorter insertion(1000);

		meter.measure([&insertion] { return insertion.Sort(); });

		REQUIRE(insertion.IsSorted());
	};

	BENCHMARK_ADVANCED("Insertion 10000")(Catch::Benchmark::Chronometer meter) {
		Sorting::InsertionSorter insertion(10000);

		meter.measure([&insertion] { return insertion.Sort(); });

		REQUIRE(insertion.IsSorted());
	};*/

	// 100k tests are really long, uncomment if you want to transform your CPU into a hot machine !
	//BENCHMARK_ADVANCED("Bubbles 100000")(Catch::Benchmark::Chronometer meter) {
	//	Sorting::InsertionSorter insertion(100000);

	//	meter.measure([&insertion] { return insertion.Sort(); });
	//};
#else
	FAIL("Insertion sort unimplemented");

#endif

}

TEST_CASE("Test Quick Sort", "[Sorting]")
{
#if QUICKSORT_IMPLEMENTED
	
	{
		std::cout << "Test Quick Sort 10" << std::endl;
		Sorting::QuickSorter quick(10);

		Timer time;
		time.start();

		quick.Sort();

		time.stop();

		REQUIRE(quick.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Quick Sort 100" << std::endl;
		Sorting::QuickSorter quick(100);

		Timer time;
		time.start();

		quick.Sort();

		time.stop();

		REQUIRE(quick.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Quick Sort 10 000" << std::endl;
		Sorting::QuickSorter quick(10000);

		Timer time;
		time.start();

		quick.Sort();

		time.stop();

		REQUIRE(quick.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Quick Sort 100 000" << std::endl;
		Sorting::QuickSorter quick(100000);

		Timer time;
		time.start();

		quick.Sort();

		time.stop();

		REQUIRE(quick.IsSorted());
		std::cout << std::endl;
	}

	/*BENCHMARK_ADVANCED("QuickSort 10")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::QuickSorter quick(10);

		meter.measure([&quick] { return quick.Sort(); });

		REQUIRE(quick.IsSorted());

	};

	BENCHMARK_ADVANCED("QuickSort 100")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::QuickSorter quick(100);

		meter.measure([&quick] { return quick.Sort(); });

		REQUIRE(quick.IsSorted());

	};

	BENCHMARK_ADVANCED("QuickSort 1000")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::QuickSorter quick(1000);

		meter.measure([&quick] { return quick.Sort(); });

		REQUIRE(quick.IsSorted());

	};

	BENCHMARK_ADVANCED("QuickSort 10000")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::QuickSorter quick(10000);

		meter.measure([&quick] { return quick.Sort(); });

		REQUIRE(quick.IsSorted());
	};*/

	// 100k tests are really long, uncomment if you want to transform your CPU into a hot machine !
	//BENCHMARK_ADVANCED("QuickSort 100000")(Catch::Benchmark::Chronometer meter) {
	//	Sorting::QuickSorter quick(100000);

	//	meter.measure([&quick] { return quick.Sort(); });

	//	REQUIRE(quick.IsSorted());
	//};
#else
	FAIL("Quick sort unimplemented");

#endif
}

TEST_CASE("Test Heap Sort", "[Sorting]")
{
#if HEAPSORT_IMPLEMENTED
	
	{
		std::cout << "Test Heap Sort 10" << std::endl;
		Sorting::HeapSorter heap(10);

		Timer time;
		time.start();

		heap.Sort();

		time.stop();

		REQUIRE(heap.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Heap Sort 100" << std::endl;
		Sorting::HeapSorter heap(100);

		Timer time;
		time.start();

		heap.Sort();

		time.stop();

		REQUIRE(heap.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Heap Sort 10 000" << std::endl;
		Sorting::HeapSorter heap(1000);

		Timer time;
		time.start();

		heap.Sort();

		time.stop();

		REQUIRE(heap.IsSorted());
		std::cout << std::endl;
	}

	{
		std::cout << "Test Heap Sort 100 000" << std::endl;
		Sorting::HeapSorter heap(100000);

		Timer time;
		time.start();

		heap.Sort();

		time.stop();

		REQUIRE(heap.IsSorted());
		std::cout << std::endl;
	}

	/*BENCHMARK_ADVANCED("HeapSort 10")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::HeapSorter heap(10);

		meter.measure([&heap] { return heap.Sort(); });

		REQUIRE(heap.IsSorted());

	};

	BENCHMARK_ADVANCED("HeapSort 100")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::HeapSorter heap(100);

		meter.measure([&heap] { return heap.Sort(); });

		REQUIRE(heap.IsSorted());

	};

	BENCHMARK_ADVANCED("HeapSort 1000")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::HeapSorter heap(1000);

		meter.measure([&heap] { return heap.Sort(); });

		REQUIRE(heap.IsSorted());

	};

	BENCHMARK_ADVANCED("HeapSort 10000")(Catch::Benchmark::Chronometer meter) {
		
		Sorting::HeapSorter heap(10000);

		meter.measure([&heap] { return heap.Sort(); });

		REQUIRE(heap.IsSorted());

	};*/

	// 100k tests are really long, uncomment if you want to transform your CPU into a hot machine !
	//BENCHMARK_ADVANCED("Bubbles 100000")(Catch::Benchmark::Chronometer meter) {
	//	Sorting::HeapSorter heap(100000);

	//	meter.measure([&heap] { return heap.Sort(); });
	//};

#else
	FAIL("Heap sort unimplemented");
#endif

}
