/**
 * *****************************************
 * @brief not to create interfaces that are too large
 * segregate the interfaces - seperate interfaces
 * @author Ajmal Rasi - mail@ajmalrasi.com
 * @version 0.1
 * @date 2020-01-23
 * *****************************************
 * 
 */

#include <vector>
struct Document;

//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much


// Interface segregation

struct IPrinter {
  virtual void print(Document& doc) = 0;
};

struct IScanner {
  virtual void scan(Document& doc) = 0;
};

struct IFax {
    virtual void fax(Document &doc) = 0;
};

struct Printer : IPrinter {
  void print(Document& doc) override;
};

struct Scanner : IScanner {
  void scan(Document& doc) override;
};

/**
 * @brief complicated interface with 
 * Scanner, Printer and Fax
 * 
 */
struct IMachine: IPrinter, IScanner, IFax {
};

struct Machine: IMachine {

  IPrinter& printer;
  IScanner& scanner;
  IFax &fax;

  Machine(IPrinter& printer, IScanner& scanner, IFax &fax)
    : printer{printer}, scanner{scanner}, fax{fax} {
  }

  void print(Document& doc) override {
    printer.print(doc);
  }

  void scan(Document& doc){
      scanner.scan(doc);
  }

  void fax(Document &doc) {
      fax.fax(doc);
  }
};

// IPrinter --> Printer
// everything --> Machine