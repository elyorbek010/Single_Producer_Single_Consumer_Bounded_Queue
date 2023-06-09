extern "C" {
#include "vector.h"
}

#include "gtest/gtest.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef _WIN32
#include <Windows.h>
void sleep(int sec) { Sleep(sec * 1000); } // Make function sleep(), compatible with unix
#else
#include <unistd.h>
#endif

typedef struct
{
	size_t vector_size;
	size_t data_amount;
	size_t producer_sleep;
	size_t consumer_sleep;
} spsc_sim_opt_t;

void spsc_simulate(spsc_sim_opt_t options);

/* Call functions with invalid(NULL) pointers*/
TEST(BASIC_OP, NULL_INPUT_TEST) {
	vector_t* vector;

	vector = vector_create(5);

	int val = 0;
	void* data_ptr = NULL;

	EXPECT_EQ(vector_push(vector, nullptr), VECTOR_SUCCESS); // NULL is a valid value

	EXPECT_EQ(vector_push(nullptr, &val), VECTOR_FAILURE);
	EXPECT_EQ(vector_push(nullptr, nullptr), VECTOR_FAILURE);

	EXPECT_EQ(vector_pop(vector, nullptr), VECTOR_FAILURE);
	EXPECT_EQ(vector_pop(nullptr, &data_ptr), VECTOR_FAILURE);
	EXPECT_EQ(vector_pop(nullptr, nullptr), VECTOR_FAILURE);

	EXPECT_EQ(vector_destroy(nullptr), VECTOR_FAILURE);

	vector_destroy(vector);
}

TEST(BASIC_OP, Push_Pop)
{
	vector_t* vector = nullptr;

	int val = 0;
	void* data_ptr = NULL;

	vector = vector_create(5);

	EXPECT_EQ(vector_push(vector, &val), VECTOR_SUCCESS);

	EXPECT_EQ(vector_pop(vector, &data_ptr), VECTOR_SUCCESS);

	EXPECT_EQ(data_ptr, &val);

	vector_destroy(vector);
}

TEST(BASIC_OP, FullVector_Overflow)
{
	vector_t* vector = nullptr;
	void* data_ptr = nullptr;

	vector = vector_create(4);

	for (size_t data_n = 0; data_n < 4; data_n++) {
		EXPECT_EQ(vector_push(vector, (void*)data_n), VECTOR_SUCCESS);
	}

	EXPECT_EQ(vector_push(vector, (void*)1), VECTOR_OVERFLOW);

	for (size_t data_n = 0; data_n < 4; data_n++) {
		EXPECT_EQ(vector_pop(vector, &data_ptr), VECTOR_SUCCESS);
		EXPECT_EQ((size_t)data_ptr, data_n);
	}

	vector_destroy(vector);
}

TEST(BASIC_OP, FullVector_Underflow)
{
	vector_t* vector = nullptr;
	void* data_ptr = nullptr;

	vector = vector_create(4);

	EXPECT_EQ(vector_pop(vector, &data_ptr), VECTOR_UNDERFLOW);

	for (size_t data_n = 0; data_n < 4; data_n++) {
		EXPECT_EQ(vector_push(vector, (void*)data_n), VECTOR_SUCCESS);
	}

	for (size_t data_n = 0; data_n < 4; data_n++) {
		EXPECT_EQ(vector_pop(vector, &data_ptr), VECTOR_SUCCESS);
		EXPECT_EQ((size_t)data_ptr, data_n);
	}

	EXPECT_EQ(vector_pop(vector, &data_ptr), VECTOR_UNDERFLOW);

	vector_destroy(vector);
}

TEST(BASIC_OP, Circulation)
{
	vector_t* vector = nullptr;
	void* data_ptr;

	vector = vector_create(5);

	// push, vector elem 5/5
	for (size_t i = 0; i < 5; i++) {
		ASSERT_EQ(vector_push(vector, (void*)i), VECTOR_SUCCESS);
	}

	// pop, vector elem 0/5
	for (size_t i = 0; i < 5; i++) {
		ASSERT_EQ(vector_pop(vector, &data_ptr), VECTOR_SUCCESS);
		ASSERT_EQ((size_t)data_ptr, i);
	}

	// push, vector elem 5/5
	for (size_t i = 6; i < 10; i++) {
		ASSERT_EQ(vector_push(vector, (void*)i), VECTOR_SUCCESS);
	}

	// pop, vector elem 0/5
	for (size_t i = 6; i < 10; i++) {
		ASSERT_EQ(vector_pop(vector, &data_ptr), VECTOR_SUCCESS);
		ASSERT_EQ((size_t)data_ptr, i);
	}

	vector_destroy(vector);
}

TEST(SPSC, Push_Pop)
{
	spsc_simulate(spsc_sim_opt_t{
		.vector_size = 1,
			.data_amount = 1,
			.producer_sleep = 0,
			.consumer_sleep = 1
		});
}

TEST(SPSC, Pop_Underflow_Push)
{
	spsc_simulate(spsc_sim_opt_t{
		.vector_size = 5,
			.data_amount = 10,
			.producer_sleep = 1,
			.consumer_sleep = 0
		});
}

TEST(SPSC, Push_Overflow_Pop)
{
	spsc_simulate(spsc_sim_opt_t{
		.vector_size = 5,
			.data_amount = 10,
			.producer_sleep = 0,
			.consumer_sleep = 1
		});
}

TEST(SPSC, FullVector_Overflow)
{
	spsc_simulate(spsc_sim_opt_t{
		.vector_size = 10,
			.data_amount = 50,
			.producer_sleep = 0,
			.consumer_sleep = 1
		});
}

void spsc_simulate(spsc_sim_opt_t options)
{
	size_t vector_size = options.vector_size;
	size_t data_amount = options.data_amount;
	size_t producer_sleep = options.producer_sleep;
	size_t consumer_sleep = options.consumer_sleep;

	vector_t* vector = vector_create(vector_size);

	size_t producer_sum = 0;
	size_t consumer_sum = 0;

	auto producer = std::thread([=, &producer_sum]()
		{
			vector_ret_t ret = VECTOR_SUCCESS;

	sleep(producer_sleep);

	for (size_t iter = 0; iter < data_amount; iter++) {

		ret = vector_push(vector, (void*)iter);

		if (ret == VECTOR_FAILURE) {
			break;
		}
		else if (ret == VECTOR_OVERFLOW) {
			iter--;
		}
		else {
			producer_sum += iter;
		}
	}

		}
	);

	auto consumer = std::thread([=, &consumer_sum]()
		{
			void* data_ptr = nullptr;
			vector_ret_t ret = VECTOR_SUCCESS;

			sleep(producer_sleep);

	for (size_t iter = 0; iter < data_amount; iter++) {

		ret = vector_pop(vector, &data_ptr);

		if (ret == VECTOR_FAILURE) {
			break;
		}
		else if (ret == VECTOR_UNDERFLOW) {
			iter--;
		}
		else {
			consumer_sum += (size_t)data_ptr;
		}
	}

		}
	);

	// join threads
	producer.join();
	consumer.join();

	vector_destroy(vector);

	// Compare the sum of pushed and popped data
	EXPECT_EQ(producer_sum, consumer_sum);
}