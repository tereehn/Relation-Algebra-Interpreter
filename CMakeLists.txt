#################################### MAKE FILE - RELATION ALGEBRA INTERPRETER ####################################
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -Wno-long-long -O0 -ggdb -lpq -lstdc++fs
TARGET = ehnovter
BUILDDIR = build
MKDIR = mkdir -p

.PHONY: all clean run compile doc

all: compile doc

compile: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(BUILDDIR)/CBinaryExpression.o $(BUILDDIR)/CCartesianExpression.o $(BUILDDIR)/CData.o $(BUILDDIR)/CData.o $(BUILDDIR)/CDataCSV.o $(BUILDDIR)/CDataSQL.o $(BUILDDIR)/CDiffExpression.o $(BUILDDIR)/CExpression.o $(BUILDDIR)/CInterface.o $(BUILDDIR)/CIntersectExpression.o $(BUILDDIR)/CJoin.o \
$(BUILDDIR)/CJoinExpression.o $(BUILDDIR)/CJoinOnExpression.o $(BUILDDIR)/CProjectExpression.o $(BUILDDIR)/CQueryHandler.o $(BUILDDIR)/CRow.o $(BUILDDIR)/CSelectExpression.o $(BUILDDIR)/CSetExpression.o $(BUILDDIR)/CSyntaxToken.o $(BUILDDIR)/CTable.o $(BUILDDIR)/CTableExpression.o $(BUILDDIR)/CTokenizer.o $(BUILDDIR)/CUnionExpression.o $(BUILDDIR)/main.o
	@echo -e "\033[1;31m [OK] \033[0m       \033[1;31m Linking:\033[0m"
	$(CXX) $(CXXFLAGS) $^ -o $@ -lpq -lstdc++fs

$(BUILDDIR)/%.o: src/%.cpp
	@echo -e "\033[1;32m [OK] \033[0m       \033[1;32m Building:\033[0m" $<
	$(MKDIR) $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@ -lpq -lstdc++fs

clean:
	@echo -e "\033[0;32m [OK] \033[0m       \033[0;33m Cleaning:\033[0m"
	rm -rf $(TARGET) $(BUILDDIR)/ *~ core *.csv 2>/dev/null
	rm -rf doc

doc:
	doxygen Doxyfile

#################################### OBJECT FILES ####################################
$(BUILDDIR)/CBinaryExpression.o: src/CBinaryExpression.cpp src/CBinaryExpression.h \
 src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CCartesianExpression.o: src/CCartesianExpression.cpp \
 src/CCartesianExpression.h src/CBinaryExpression.h src/CExpression.h \
 src/CTable.h src/CRow.h
$(BUILDDIR)/CData.o: src/CData.cpp src/CData.h src/CTable.h src/CRow.h
$(BUILDDIR)/CDataCSV.o: src/CDataCSV.cpp src/CDataCSV.h src/CData.h src/CTable.h \
 src/CRow.h
$(BUILDDIR)/CDataSQL.o: src/CDataSQL.cpp src/CDataSQL.h src/CData.h src/CTable.h \
 src/CRow.h
$(BUILDDIR)/CDiffExpression.o: src/CDiffExpression.cpp src/CDiffExpression.h \
 src/CSetExpression.h src/CBinaryExpression.h src/CExpression.h \
 src/CTable.h src/CRow.h
$(BUILDDIR)/CExpression.o: src/CExpression.cpp src/CExpression.h src/CTable.h \
 src/CRow.h
$(BUILDDIR)/CInterface.o: src/CInterface.cpp src/CInterface.h src/CData.h \
 src/CTable.h src/CRow.h src/CDataCSV.h src/CDataSQL.h \
 src/CQueryHandler.h src/CTokenizer.h src/CSyntaxToken.h \
 src/CSyntaxKind.h src/CExpression.h
$(BUILDDIR)/CIntersectExpression.o: src/CIntersectExpression.cpp \
 src/CIntersectExpression.h src/CSetExpression.h src/CBinaryExpression.h \
 src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CJoin.o: src/CJoin.cpp src/CJoin.h src/CBinaryExpression.h \
 src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CJoinExpression.o: src/CJoinExpression.cpp src/CJoinExpression.h \
 src/CJoin.h src/CBinaryExpression.h src/CExpression.h src/CTable.h \
 src/CRow.h
$(BUILDDIR)/CJoinOnExpression.o: src/CJoinOnExpression.cpp src/CJoinOnExpression.h \
 src/CJoin.h src/CBinaryExpression.h src/CExpression.h src/CTable.h \
 src/CRow.h
$(BUILDDIR)/CProjectExpression.o: src/CProjectExpression.cpp src/CProjectExpression.h \
 src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CQueryHandler.o: src/CQueryHandler.cpp src/CQueryHandler.h \
 src/CTokenizer.h src/CSyntaxToken.h src/CSyntaxKind.h src/CTable.h \
 src/CRow.h src/CExpression.h src/CTableExpression.h \
 src/CProjectExpression.h src/CJoinExpression.h src/CJoin.h \
 src/CBinaryExpression.h src/CJoinOnExpression.h src/CUnionExpression.h \
 src/CSetExpression.h src/CIntersectExpression.h \
 src/CCartesianExpression.h src/CDiffExpression.h src/CSelectExpression.h
$(BUILDDIR)/CRow.o: src/CRow.cpp src/CRow.h
$(BUILDDIR)/CSelectExpression.o: src/CSelectExpression.cpp src/CSelectExpression.h \
 src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CSetExpression.o: src/CSetExpression.cpp src/CSetExpression.h \
 src/CBinaryExpression.h src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CSyntaxToken.o: src/CSyntaxToken.cpp src/CSyntaxToken.h src/CSyntaxKind.h
$(BUILDDIR)/CTable.o: src/CTable.cpp src/CTable.h src/CRow.h
$(BUILDDIR)/CTableExpression.o: src/CTableExpression.cpp src/CTableExpression.h \
 src/CExpression.h src/CTable.h src/CRow.h
$(BUILDDIR)/CTokenizer.o: src/CTokenizer.cpp src/CTokenizer.h src/CSyntaxToken.h \
 src/CSyntaxKind.h
$(BUILDDIR)/CUnionExpression.o: src/CUnionExpression.cpp src/CUnionExpression.h \
 src/CSetExpression.h src/CBinaryExpression.h src/CExpression.h \
 src/CTable.h src/CRow.h
$(BUILDDIR)/main.o: src/main.cpp src/CInterface.h src/CData.h src/CTable.h src/CRow.h
