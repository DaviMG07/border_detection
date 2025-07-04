IVERILOG = iverilog
VVP = vvp
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
CFC_SRC = $(SRC_DIR)/cfc.v $(SRC_DIR)/mac.v
MAC_SRC = $(SRC_DIR)/mac.v
CFC_TB_SRC = $(TEST_DIR)/cfc_tb.v
MAC_TB_SRC = $(TEST_DIR)/mac_tb.v
CFC_TB_OUT = $(BIN_DIR)/cfc_tb
MAC_TB_OUT = $(BIN_DIR)/mac_tb
.PHONY: all test run_cfc_tb run_mac_tb clean
all: $(CFC_TB_OUT) $(MAC_TB_OUT)
$(CFC_TB_OUT): $(CFC_SRC) $(CFC_TB_SRC)
	@echo "Compiling CFC testbench..."
	@mkdir -p $(BIN_DIR)
	$(IVERILOG) -o $@ $^
$(MAC_TB_OUT): $(MAC_SRC) $(MAC_TB_SRC)
	@echo "Compiling MAC testbench..."
	@mkdir -p $(BIN_DIR)
	$(IVERILOG) -o $@ $^
run_cfc_tb: $(CFC_TB_OUT)
	@echo "Running CFC testbench..."
	$(VVP) $<
run_mac_tb: $(MAC_TB_OUT)
	@echo "Running MAC testbench..."
	$(VVP) $<
test: run_cfc_tb run_mac_tb
clean:
	@echo "Cleaning up..."
	@rm -f $(BIN_DIR)/*
