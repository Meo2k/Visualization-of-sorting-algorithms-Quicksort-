# Đặt tên cho file thực thi
TARGET = new

# Đặt đường dẫn
SRCDIR = ../src
INCDIR = $(SRCDIR)/include
LIBDIR = $(SRCDIR)/lib
NEWDIR = .

# Các file mã nguồn và đối tượng
SOURCES = $(NEWDIR)/quicksort.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Lựa chọn trình biên dịch
CXX = g++
CXXFLAGS = -std=c++11 -I$(INCDIR)
LDFLAGS = -L$(LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Mục tiêu mặc định
all: $(TARGET)

# Quy tắc để tạo file thực thi
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Quy tắc để biên dịch các file mã nguồn thành file đối tượng
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Quy tắc dọn dẹp
clean:
	rm -f $(OBJECTS) $(TARGET)

# Mục tiêu để biên dịch và chạy chương trình
run: $(TARGET)
	./$(TARGET)
