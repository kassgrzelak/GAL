//
// Created by kassie on 21/01/2026.
//

#include <catch2/catch_test_macros.hpp>
#define GAL_DEV_TESTING
#include <GAL/gal.hpp>

void testDeleterPtr(int* ptr) noexcept
{
	REQUIRE(ptr != nullptr);
	delete ptr;
}

void testDeleterUint(unsigned int handle) noexcept
{
	REQUIRE(handle != static_cast<unsigned int>(-1));
}

TEST_CASE (
"UniqueHandle basic pointer operations"
,
"[UniqueHandle]"
)
{
	using namespace gal::detail;
	using TestUniqueHandlePtr = UniqueHandle<int*, nullptr, testDeleterPtr>;

	TestUniqueHandlePtr a;
	REQUIRE(!a.handleValid());

	auto i1 = new int{1};
	a.setHandle(i1);
	REQUIRE(a.handleValid());
	REQUIRE(a.getHandle() == i1);

	SECTION("Move constructor") {
		TestUniqueHandlePtr b(std::move(a));
		REQUIRE(!a.handleValid());
		REQUIRE(b.handleValid());
		REQUIRE(b.getHandle() == i1);
	}
}

TEST_CASE (
"UniqueHandle basic uint operations"
,
"[UniqueHandle]"
)
{
	using namespace gal::detail;
	using TestUniqueHandleUint = UniqueHandle<unsigned int, static_cast<unsigned int>(-1), testDeleterUint>;

	TestUniqueHandleUint a;
	REQUIRE(!a.handleValid());

	unsigned int i1 = 3;
	a.setHandle(i1);
	REQUIRE(a.handleValid());
	REQUIRE(a.getHandle() == i1);

	SECTION("Move constructor")
	{
		TestUniqueHandleUint b(std::move(a));
		REQUIRE(!a.handleValid());
		REQUIRE(b.handleValid());
		REQUIRE(b.getHandle() == i1);
	}
}

TEST_CASE (
"UniqueHandle with ResourceRegistry"
,
"[UniqueHandle][ResourceRegistry]"
)
{
	using namespace gal::detail;
	using TestUniqueHandlePtr = UniqueHandle<int*, nullptr, testDeleterPtr>;

	SECTION("Normal destroyAll()")
	{
		resourceRegistry = ResourceRegistry{};

		auto i1 = new int{1};
		TestUniqueHandlePtr a{i1};

		REQUIRE(resourceRegistry.contains(a.getHandlePtr()));
		resourceRegistry.destroyAll();
		REQUIRE(!a.handleValid());
		REQUIRE(!resourceRegistry.contains(a.getHandlePtr()));
	}

	SECTION("RAII auto-destruction")
	{
		resourceRegistry = ResourceRegistry{};

		auto i2 = new int{2};
		void* bPtr;

		{
			TestUniqueHandlePtr b{i2};
			bPtr = b.getHandlePtr();
		}

		REQUIRE(*i2 != 2);
		REQUIRE(!resourceRegistry.contains(bPtr));
	}

	SECTION("destroyAll() in scope, check out of scope")
	{
		resourceRegistry = ResourceRegistry{};

		auto i3 = new int{3};
		void* cPtr;

		{
			TestUniqueHandlePtr c{i3};
			cPtr = c.getHandlePtr();
			resourceRegistry.destroyAll();
		}

		REQUIRE(*i3 != 3);
		REQUIRE(!resourceRegistry.contains(cPtr));
	}
}