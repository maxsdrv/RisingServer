#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <MainBus.h>

using namespace boost::unit_test;

class TestModes{
public:
	TestModes() : main_bus_test(std::make_shared<MainBus>()) {}

	void test_controller() {
		BOOST_TEST(main_bus_test->create_controller(BUSLINE::MKO_BUS_A) != nullptr);
	}
	void test_abonent() {
		BOOST_TEST(main_bus_test->create_abonent(BUSLINE::MKO_BUS_A, 0) != nullptr);
	}
	void test_monitor() {
		BOOST_TEST(main_bus_test->create_monitor() != nullptr);
	}
private:
	std::shared_ptr<MainBus> main_bus_test;
};

test_suite* init_unit_test_suite(int argc, char* argv[]) {

	std::shared_ptr<TestModes> tester(new TestModes);
	framework::master_test_suite().add(BOOST_TEST_CASE([tester] {tester->test_controller(); }));
	framework::master_test_suite().add(BOOST_TEST_CASE([tester] {tester->test_abonent(); }));
	framework::master_test_suite().add(BOOST_TEST_CASE([tester] {tester->test_monitor(); }));

	return nullptr;
}
