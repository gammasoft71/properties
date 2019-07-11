#include <xtd/xtd.properties.hpp>
#include <xtd/xtd.tunit>

using namespace xtd;
using namespace xtd::tunit;

namespace unit_tests {
  class test_class_(test_read_only_property) {
  public:
    void test_method_(create_with_implicit_cast_operator) {
      int v = 42;
      property_<int, readonly_> value {
        get_ {return v;}
      };
      
      assert::are_equal(42, value);
    }

    void test_method_(get_functor) {
      int v = 42;
      property_<int, readonly_> value {
        get_ {return v;}
      };
      
      assert::are_equal(42, value());
    }

    void test_method_(get_function) {
      int v = 42;
      property_<int, readonly_> value {
        get_ {return v;}
      };
      
      assert::are_equal(42, value.get());
    }

    void test_method_(equality_operator) {
      int v = 42;
      property_<int, readonly_> value {
        get_ {return v;}
      };
      
      assert::is_true(value == 42);
      assert::is_false(value == 84);
    }

    void test_method_(inequality_operator) {
      int v = 42;
      property_<int, readonly_> value {
        get_ {return v;}
      };
      
      assert::is_false(value != 42);
      assert::is_true(value != 84);
    }

    class property_read_only {
    public:
      property_read_only() {}
      property_read_only(const property_read_only& prw) : name_(prw.name_) {}
      property_read_only& operator=(const property_read_only& prw) = default;
      
      property_<std::string, readonly_> name {
        get_ {return this->name_;}
      };
      
    private:
      std::string name_ = "Test property";
    };

    void test_method_(create_using_copy_constructor) {
      std::shared_ptr<property_read_only> property_read_only1 = std::make_shared<property_read_only>();
      std::shared_ptr<property_read_only> property_read_only2 = std::make_shared<property_read_only>(*property_read_only1);
      property_read_only1 = nullptr;

      assert::is_null(property_read_only1);
      assert::are_equal("Test property", property_read_only2->name);
    }
    
    void test_method_(create_using_copy_opearotor) {
      std::shared_ptr<property_read_only> property_read_only1 = std::make_shared<property_read_only>();
      std::shared_ptr<property_read_only> property_oead_only2 = std::make_shared<property_read_only>();
      *property_oead_only2 = *property_read_only1;
      property_read_only1 = nullptr;

      assert::is_null(property_read_only1);
      assert::are_equal("Test property", property_oead_only2->name);
    }
 };
}
