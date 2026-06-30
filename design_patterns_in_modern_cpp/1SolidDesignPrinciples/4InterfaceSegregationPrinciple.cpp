#include <iostream>

namespace CombinedInterface {

struct Document;

// lets say you want to implement an interface to process the documents like
// printing, scanning and fax. You could define something like the following
struct IMachine {

  virtual void print(Document &doc) = 0;
  virtual void scan(Document &doc) = 0;
  virtual void fax(Document &doc) = 0;
};

struct MultiFileProcessor : public IMachine {

  void print(Document &doc) override {};
  void scan(Document &doc) override {};
  void fax(Document &doc) override {};
};

// the above one is okay, if we want to implement all three. But what if we want
// to implement just a scanner or printer or fax only.
// The following is okay but what do we put for print and fax. We can leave them
// empty but it sends a wrong message for a client using it. So that's when we
// need to segregate interfaces.
struct Scanner : IMachine {
  void print(Document &doc) override {};
  void scan(Document &doc) override {
    // Do something related to scanner
  };
  void fax(Document &doc) override {};
};

} // namespace CombinedInterface

// so now lets segregate interfaces.
// Core of the interface segregation principle is to avoid stuffing too much
// into a single interface. So you don't want to force the client to implement
// too much. Just breakup your interfaces into separate interfaces or just at
// lease make them smaller so that whenever a client uses one of those chunks,
// its all coherent
namespace SegregateInterface {

struct Document;

// now we can have separate interfaces for for all three machines
struct IPrinter {
  virtual void print(Document &doc) = 0;
};

struct IScanner {
  virtual void scan(Document &doc) = 0;
};

struct IFax {
  virtual void fax(Document &doc) = 0;
};

// now if someone wants to implement only printer
struct Printer : IPrinter {
  void print(Document &doc) override {}
};

struct Scanner : IScanner {
  void scan(Document &doc) override {}
};
// And if someone wants to implement multiple file processor, then they can
// define one more interface
struct IMultiFileProcessor : IPrinter, IScanner {};

// now concrete implementation of that
// We can build the decorator (which is one more pattern)
struct MultiFileProcessor : IMultiFileProcessor {
  // lets have reference to IPrinter and IScanner
  // aggregated
  IPrinter &printer;
  IScanner &scanner;
  MultiFileProcessor(IPrinter &printer, IScanner &scanner)
      : printer(printer), scanner(scanner) {}
  // now we can implement members of interms of the things we have aggregated
  void print(Document &doc) override { printer.print(doc); }
  void scan(Document &doc) override { scanner.scan(doc); }
};

} // namespace SegregateInterface
