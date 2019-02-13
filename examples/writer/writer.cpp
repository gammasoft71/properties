#include <xtd/properties.hpp>
#include <iostream>
#include <memory>
#include <string>

class Writer {
public:
  virtual ~Writer() {}
  virtual void Write(const std::string& string) = 0;
  virtual void WriteLine(const std::string& string) = 0;
};

class ConsoleWriter : public Writer {
public:
  void Write(const std::string& string) override {
    std::cout << string;
  }

  void WriteLine(const std::string& string) override {
    this->Write(string);
    std::cout << std::endl;
  }
};

class TestWriter {
public:
  TestWriter() = default;

  property_<std::shared_ptr<::Writer>, writeonly_> Writer {
    set_ {
      this->writer = value;
      this->writer->WriteLine("set new Writer...");
    }
  };

  void DoSomething() {
    if (this->writer != nullptr)
      this->writer->WriteLine("DoSomething...");
  }

  void DoOtherthing() {
    if (this->writer != nullptr)
      this->writer->WriteLine("DoOtherthing...");
  }

private:
  std::shared_ptr<::Writer> writer;
};

int main(int argc, char* argv[]) {
  TestWriter testWriter;

  std::cout << "TestWriter without Writer :" << std::endl;
  testWriter.DoSomething();
  testWriter.DoOtherthing();
  std::cout << std::endl;

  std::cout << "TestWriter with ConsoleWriter :" << std::endl;
  testWriter.Writer = std::make_shared<ConsoleWriter>();
  testWriter.DoSomething();
  testWriter.DoOtherthing();
  std::cout << std::endl;
}

// This code produces the following output :
//
// TestWriter without Writer :
//
// TestWriter with ConsoleWriter :
// set new Writer...
// DoSomething...
// DoOtherthing...
