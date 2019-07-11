#include <xtd/xtd.properties.hpp>
#include <xtd/xtd.tunit>

using namespace xtd;
using namespace xtd::tunit;

namespace unit_tests {
  class test_class_(test_write_only_property) {
  public:
    void test_method_(create_and_set_with_equal_operator) {
      int v = 42;
      property_<int, writeonly_> value {
        set_ {v = value;}
      };
      
      value = 24;
      assert::are_equal(24, v);
    }
    
    void test_method_(create_and_set_with_functor) {
      int v = 42;
      property_<int, writeonly_> value {
        set_ {v = value;}
      };
      
      value(24);
      assert::are_equal(24, v);
    }
    
    void test_method_(create_and_set_with_set_method) {
      int v = 42;
      property_<int, writeonly_> value {
        set_ {v = value;}
      };
      
      value.set(24);
      assert::are_equal(24, v);
    }
    
    class property_write_only {
    public:
      property_write_only() {}
      property_write_only(const property_write_only& prw) : name_(prw.name_) {}
      property_write_only& operator=(const property_write_only& prw) = default;
      
      property_<std::string, writeonly_> name {
        set_ {this->name_ = value;}
      };
      
      std::string name_ = "Test property";
    };

    void test_method_(create_using_copy_constructor) {
      std::shared_ptr<property_write_only> property_write_only1 = std::make_shared<property_write_only>();
      std::shared_ptr<property_write_only> property_write_only2 = std::make_shared<property_write_only>(*property_write_only1);
      property_write_only1 = nullptr;
      
      assert::is_null(property_write_only1);
      assert::are_equal("Test property", property_write_only2->name_);
      
      property_write_only2->name = "Other thing";
      
      assert::are_equal("Other thing", property_write_only2->name_);
    }
    
    void test_method_(create_using_copy_operator) {
      std::shared_ptr<property_write_only> property_write_only1 = std::make_shared<property_write_only>();
      std::shared_ptr<property_write_only> property_write_only2 = std::make_shared<property_write_only>();
      *property_write_only2 = *property_write_only1;
      property_write_only1 = nullptr;
      
      assert::is_null(property_write_only1);
      assert::are_equal("Test property", property_write_only2->name_);
      
      property_write_only2->name = "Other thing";
      
      assert::are_equal("Other thing", property_write_only2->name_);
    }
  };
}
