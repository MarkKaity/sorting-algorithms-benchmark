# THỰC NGHIỆM VÀ ĐÁNH GIÁ CÁC THUẬT TOÁN SẮP XẾP
> **Học phần:** Cấu trúc dữ liệu và Giải thuật (IT003)  
> **Nhiệm vụ:** Thực nghiệm, đo lường và so sánh hiệu năng của 4 thuật toán: **QuickSort**, **HeapSort**, **MergeSort** và **`std::sort` (C++)** trên 10 bộ dữ liệu kích thước lớn ($N = 1.000.000$ số thực).  
> **Môi trường thực nghiệm:** **MSYS2 UCRT64** (GCC 14+ / C++17), tận dụng cơ chế điều hướng luồng dữ liệu chuẩn Unix (Standard I/O Redirection).

---

## MỤC LỤC
1. [Cấu trúc thư mục dự án](#1-cấu-trúc-thư-mục-dự-án)
2. [Tổng quan môi trường MSYS2 UCRT64](#2-tổng-quan-môi-trường-msys2-ucrt64)
3. [Phân tích chuyên sâu Bước 1: Khởi tạo dữ liệu thử nghiệm](#3-phân-tích-chuyên-sâu-bước-1-khởi-tạo-dữ-liệu-thử-nghiệm)
   - [3.1. Thiết kế 10 bộ dữ liệu và ý nghĩa thực nghiệm](#31-thiết-kế-10-bộ-dữ-liệu-và-ý-nghĩa-thực-nghiệm)
   - [3.2. Cơ chế chuyển hướng luồng (`>`) trong MSYS2 Terminal](#32-cơ-chế-chuyển-hướng-luồng--trong-msys2-terminal)
   - [3.3. Giải pháp kỹ thuật và tối ưu hóa hiệu năng](#33-giải-pháp-kỹ-thuật-và-tối-ưu-hóa-hiệu-năng)
4. [Hướng dẫn thực hành chi tiết từng bước (Step-by-Step Tutorial)](#4-hướng-dẫn-thực-hành-chi-tiết-từng-bước-step-by-step-tutorial)
   - [Bước 1: Khởi động MSYS2 UCRT64](#bước-1-khởi-động-msys2-ucrt64)
   - [Bước 2: Tải mã nguồn & Di chuyển vào thư mục dự án](#bước-2-tải-mã-nguồn--di-chuyển-vào-thư-mục-dự-án)
   - [Bước 3: Biên dịch mã nguồn sinh dữ liệu](#bước-3-biên-dịch-mã-nguồn-sinh-dữ-liệu)
   - [Bước 4: Thực thi tạo 10 file dữ liệu bằng lệnh `>`](#bước-4-thực-thi-tạo-10-file-dữ-liệu-bằng-lệnh-)
   - [Bước 5: Thẩm định và kiểm tra tính toàn vẹn của dữ liệu](#bước-5-thẩm-định-và-kiểm-tra-tính-toàn-vẹn-của-dữ-liệu)
5. [Lộ trình các bước kế tiếp](#5-lộ-trình-các-bước-kế-tiếp)

---

## 1. CẤU TRÚC THƯ MỤC DỰ ÁN

```text
SORT Report/
├── data/                      # Chứa 10 bộ dữ liệu kiểm thử (test_01.txt -> test_10.txt)
├── src/
│   ├── gen_asc.cpp            # Sinh dữ liệu tăng dần (Ascending) ra stdout
│   ├── gen_desc.cpp           # Sinh dữ liệu giảm dần (Descending) ra stdout
│   ├── gen_random.cpp         # Sinh dữ liệu ngẫu nhiên (Random) ra stdout
│   ├── quick_sort.cpp         # Cài đặt QuickSort (Median-of-three pivot)
│   ├── heap_sort.cpp          # Cài đặt HeapSort
│   ├── merge_sort.cpp         # Cài đặt MergeSort
│   ├── std_sort.cpp           # Sử dụng std::sort (C++)
│   └── benchmark.cpp          # Bộ điều khiển đo lường tự động (ms)
├── results/
│   ├── benchmark_results.csv  # Bảng số liệu thời gian thực thi
│   └── chart_comparison.png   # Biểu đồ cột so sánh hiệu năng
├── report/
│   ├── Sorting_Report.docx    # Báo cáo theo mẫu chuẩn
│   └── Sorting_Report.pdf     # File PDF hoàn chỉnh nộp bài (kèm link GitHub)
├── generate_all.sh            # Script Bash tự động sinh toàn bộ 10 file qua MSYS2
├── README.md                  # Hướng dẫn chi tiết & tài liệu phân tích
└── .gitignore                 # Bỏ qua file nhị phân và dữ liệu lớn trên Git
```

---

## 2. TỔNG QUAN MÔI TRƯỜNG MSYS2 UCRT64

### 2.1. Tại sao sử dụng MSYS2 UCRT64?
* **MSYS2 (Minimal SYStem 2):** Cung cấp môi trường dòng lệnh chuẩn POSIX/Unix (Bash shell, GNU utilities như `make`, `grep`, `head`, `tail`, `wc`) ngay trên hệ điều hành Windows.
* **Môi trường UCRT64 (Universal C Runtime):** Là môi trường được khuyến nghị hiện đại nhất của MSYS2, sử dụng `ucrtbase.dll` của Windows 10/11, hỗ trợ C++17/C++20 đầy đủ, tốc độ tính toán số thực và thao tác I/O nhanh hơn đáng kể so với MSVCRT cũ.
* **Trình biên dịch:** `g++` (bộ công cụ GCC 64-bit trong môi trường UCRT64). Nếu máy bạn chưa có, chỉ cần cài đặt bằng 1 lệnh duy nhất trong MSYS2:
  ```bash
  pacman -S --needed mingw-w64-ucrt-x86_64-gcc
  ```

### 2.2. Quy ước chuyển đổi đường dẫn giữa Windows và MSYS2 Bash
Vì MSYS2 mô phỏng hệ thống tệp tin Unix, các ký hiệu ổ đĩa của Windows sẽ được chuyển đổi theo quy tắc:
* **Tên ổ đĩa:** Ký tự ổ đĩa chuyển thành chữ thường và đặt sau dấu gạch chéo `/`:
  * `C:\...` $\longrightarrow$ `/c/...`
  * `D:\...` $\longrightarrow$ `/d/...`
* **Dấu phân cách:** Dấu gạch chéo ngược `\` của Windows đổi thành dấu gạch chéo xuôi `/`.
* **Khoảng trắng trong tên thư mục:** Bắt buộc phải đặt toàn bộ đường dẫn trong cặp dấu nháy kép `""` hoặc dùng dấu thoát `\ ` trước khoảng trắng.
  * Ví dụ đường dẫn Windows: `C:\Users\TenBan\Documents\Bai Tap Lon`
  * Đường dẫn tương ứng trong MSYS2: `"/c/Users/TenBan/Documents/Bai Tap Lon"`

---

## 3. PHÂN TÍCH CHUYÊN SÂU BƯỚC 1: KHỞI TẠO DỮ LIỆU THỬ NGHIỆM

---

### 3.1. Thiết kế 10 bộ dữ liệu và ý nghĩa thực nghiệm

Mỗi bộ dữ liệu bao gồm **1.000.000 số thực độ chính xác kép (`double`)**. Thiết kế 10 bộ dữ liệu phục vụ trực tiếp cho việc đánh giá độ phức tạp thuật toán ở các trường hợp khác nhau:

| Bộ dữ liệu | Tên file | Đặc điểm phân bổ | Mục đích thực nghiệm |
| :---: | :---: | :--- | :--- |
| **Dãy 1** | `data/test_01.txt` | **Tăng dần** (Sorted Ascending) | Kiểm tra trường hợp tốt nhất hoặc phát hiện lỗi của QuickSort (nguy cơ suy biến thành $O(N^2)$ nếu chọn chốt kém). |
| **Dãy 2** | `data/test_02.txt` | **Giảm dần** (Sorted Descending) | Kiểm tra khả năng xử lý khi mảng bị đảo ngược thứ tự 100%. |
| **Dãy 3 – 10** | `data/test_03.txt` $\rightarrow$ `data/test_10.txt` | **Ngẫu nhiên hoàn toàn** (Uniformly Random) | Đại diện cho trường hợp trung bình (Average Case), mỗi file sử dụng một hạt giống ngẫu nhiên (seed) riêng biệt nhằm đảm bảo tính độc lập thống kê. |

* **Quy cách cấu trúc file:**
  * Dòng 1: Ghi số lượng phần tử $N = 1000000$.
  * $N$ dòng tiếp theo: Mỗi dòng ghi đúng 1 số thực lấy 6 chữ số thập phân (`fixed` precision, ví dụ `123456.789012`).
  * Dung lượng: $\approx 15\text{ MB}$ cho mỗi file, tổng cộng $\approx 150\text{ MB}$ cho 10 file.

---

### 3.2. Cơ chế chuyển hướng luồng (`>`) trong MSYS2 Terminal

Thay vì ép chương trình C++ tự mở file và ghi đĩa bên trong code, ta thiết kế chương trình theo **Triết lý Unix (Unix Philosophy)**:
> *"Write programs that do one thing and do it well. Write programs to handle text streams, because that is a universal interface."*

```mermaid
flowchart LR
    A["Chương trình C++<br/>(generate_data)"] -->|"stdout<br/>(std::cout)"| B["Terminal MSYS2"]
    B -->|"Toán tử chuyển hướng >"| C["File đĩa cứng<br/>(data/test_01.txt)"]
```

#### Phân tích cơ chế hoạt động:
1. **Luồng xuất tiêu chuẩn (`stdout` - File Descriptor 1):** Chương trình `generate_data` chỉ tập trung sinh số ngẫu nhiên và in kết quả ra màn hình thông qua luồng `std::cout`.
2. **Toán tử `>` (Redirect Standard Output):** Khi người dùng gõ:
   ```bash
   ./generate_data 1 > data/test_01.txt
   ```
   Shell Bash của MSYS2 sẽ chặn toàn bộ dữ liệu đi ra màn hình và chuyển hướng ghi trực tiếp vào file `data/test_01.txt`. Nếu file chưa có, shell sẽ tự động tạo mới; nếu file đã có, shell sẽ ghi đè.
3. **Luồng thông báo lỗi (`stderr` - File Descriptor 2):** Các thông điệp hướng dẫn, cảnh báo lỗi được xuất qua `std::cerr`. Do đó, dù có chuyển hướng `>` thì thông báo hướng dẫn vẫn hiện trên màn hình mà không làm lẫn rác vào file dữ liệu.

---

### 3.3. Giải pháp kỹ thuật và tối ưu hóa hiệu năng

#### a. Bộ sinh số ngẫu nhiên chất lượng cao (`<random>`):
* Hàm `rand()` cổ điển của thư viện C có chu kỳ cực ngắn ($2^{31}-1$) và hằng số `RAND_MAX` chỉ đạt $32.767$, không thể sinh được dữ liệu ngẫu nhiên đa dạng cho 1 triệu phần tử.
* Giải pháp: Sử dụng bộ sinh **Mersenne Twister 64-bit** (`std::mt19937_64`) có chu kỳ cực lớn $2^{19937}-1$.
* Kết hợp với phân phối thực đều `std::uniform_real_distribution<double>(0.0, 1000000.0)`.

#### b. Tính tái lập dữ liệu (Reproducibility):
* Tham số truyền vào chương trình (ví dụ `1`, `2`, `3`... `10`) được dùng để tính toán hạt giống cố định (`seed = 123456789ULL + testId * 987654321ULL`).
* Điều này giúp mọi thành viên hoặc người chấm khi chạy lại lệnh đều thu được **chính xác cùng một bộ dữ liệu**, đảm bảo tính khoa học và minh bạch của bài thực nghiệm.

#### c. Tối ưu hóa I/O tốc độ cao (Fast I/O):
* Xuất 1.000.000 số thực ra màn hình/file có thể mất 20–30 giây nếu dùng cách thông thường.
* Để giảm thời gian xuống **dưới 1 giây**:
  1. `std::ios_base::sync_with_stdio(false);`: Tắt cơ chế đồng bộ giữa thư viện C++ và C runtime.
  2. `std::cin.tie(nullptr);`: Gỡ liên kết `cin` và `cout`.
  3. Dùng ký tự xuống dòng `\n` thay cho `std::endl` (vì `std::endl` luôn ép gọi lệnh xả bộ đệm `flush()`, gây nghẽn I/O hệ thống).

---

## 4. HƯỚNG DẪN THỰC HÀNH CHI TIẾT TỪNG BƯỚC (STEP-BY-STEP TUTORIAL)

Mọi thao tác dưới đây đều được thực hiện bên trong cửa sổ dòng lệnh của **MSYS2**.

---

### Bước 1: Khởi động MSYS2 UCRT64
1. Mở **Start Menu** trên Windows, tìm kiếm và khởi chạy **MSYS2 UCRT64**.  
   *(Hoặc mở file `ucrt64.exe` trong thư mục bạn đã cài đặt MSYS2, thông thường là `C:\msys64\ucrt64.exe` hoặc `D:\MSYS2\ucrt64.exe`)*.
2. Kiểm tra trình biên dịch GCC bằng lệnh:
   ```bash
   g++ --version
   ```
   *Nếu hiển thị thông tin phiên bản g++ (14.x hoặc 16.x) là đã sẵn sàng. Nếu chưa có, chạy lệnh sau để cài đặt: `pacman -S --needed mingw-w64-ucrt-x86_64-gcc`*.

---

### Bước 2: Tải mã nguồn & Di chuyển vào thư mục dự án

Tùy vào cách bạn lấy mã nguồn từ GitHub về máy tính cá nhân:

#### Trường hợp A: Sử dụng lệnh Git Clone (Khuyên dùng - Nhanh và tự động)
Trong terminal MSYS2, bạn gõ lệnh clone trực tiếp từ GitHub, sau đó `cd` vào tên repository:
```bash
# 1. Tải toàn bộ mã nguồn về máy
git clone https://github.com/<tai-khoan-github>/<ten-repo>.git

# 2. Di chuyển vào thư mục vừa clone
cd <ten-repo>
```
*(Với cách này, bạn không cần quan tâm mã nguồn đang ở ổ đĩa C hay D vì terminal sẽ tự động theo dấu thư mục hiện hành).*

#### Trường hợp B: Nếu bạn tải file ZIP từ GitHub về máy và giải nén
Sau khi giải nén ra một thư mục bất kỳ trên máy bạn (ví dụ thư mục `Downloads` hoặc `Desktop`), hãy dùng một trong hai cách sau để `cd` vào thư mục:

* **Mẹo 1: Kéo & Thả chuột (Drag & Drop - Cực kỳ tiện lợi):**
  1. Trong cửa sổ MSYS2, gõ: `cd "` *(lưu ý: có dấu cách và dấu nháy kép mở)*.
  2. Mở File Explorer trên Windows, kéo thư mục dự án vừa giải nén thả trực tiếp vào cửa sổ MSYS2 (terminal sẽ tự động dán và chuyển đổi đường dẫn Windows thành đường dẫn MSYS2).
  3. Gõ tiếp dấu nháy kép đóng `"` và nhấn `Enter`.

* **Mẹo 2: Tự gõ lệnh `cd` theo quy tắc chuyển đổi đường dẫn:**
  Chuyển đổi đường dẫn Windows của máy bạn sang chuẩn Unix theo [mục 2.2](#22-quy-ước-chuyển-đổi-đường-dẫn-giữa-windows-và-msys2-bash):
  * Ví dụ máy bạn lưu tại `C:\Users\Admin\Downloads\SORT-Report`:
    ```bash
    cd "/c/Users/Admin/Downloads/SORT-Report"
    ```
  * Ví dụ máy bạn lưu tại `D:\BaiTap\SORT Report`:
    ```bash
    cd "/d/BaiTap/SORT Report"
    ```

> [!TIP]
> **Cách kiểm tra bạn đã ở đúng thư mục dự án hay chưa:**  
> Gõ lệnh `ls` trong terminal:
> ```bash
> ls
> ```
> Nếu màn hình hiển thị danh sách có chứa: `generate_all.sh`, `README.md`, `src/`... tức là bạn đã định vị chính xác!

---

### Bước 3: Biên dịch 3 file mã nguồn sinh dữ liệu
Dự án chia làm 3 chương trình C++ độc lập cho 3 kiểu dữ liệu để dễ quản lý:
1. [src/gen_asc.cpp](file:///d:/SORT%20Report/src/gen_asc.cpp): Sinh dãy số tăng dần (Ascending).
2. [src/gen_desc.cpp](file:///d:/SORT%20Report/src/gen_desc.cpp): Sinh dãy số giảm dần (Descending).
3. [src/gen_random.cpp](file:///d:/SORT%20Report/src/gen_random.cpp): Sinh dãy số ngẫu nhiên (Random).

Biên dịch cả 3 file bằng trình biên dịch `g++` với cờ tối ưu hóa `-O3` và chuẩn C++17:
```bash
g++ -std=c++17 -O3 src/gen_asc.cpp -o gen_asc
g++ -std=c++17 -O3 src/gen_desc.cpp -o gen_desc
g++ -std=c++17 -O3 src/gen_random.cpp -o gen_random
```

---

### Bước 4: Thực thi tạo 10 file dữ liệu bằng lệnh `>`

Trước tiên, hãy đảm bảo thư mục chứa dữ liệu `data` đã được tạo:
```bash
mkdir -p data
```

Bây giờ, bạn thực hiện lệnh sinh dữ liệu kết hợp toán tử chuyển hướng `>` trong MSYS2:

#### 1. Sinh Dãy 1 (Tăng dần - Dùng `gen_asc`):
```bash
./gen_asc > data/test_01.txt
```

#### 2. Sinh Dãy 2 (Giảm dần - Dùng `gen_desc`):
```bash
./gen_desc > data/test_02.txt
```

#### 3. Sinh 8 Dãy ngẫu nhiên (Dãy 3 đến Dãy 10 - Dùng `gen_random`):
Bạn có thể truyền số thứ tự `3..10` làm seed để kết quả ngẫu nhiên có tính tái lập:
```bash
./gen_random 3 > data/test_03.txt
./gen_random 4 > data/test_04.txt
./gen_random 5 > data/test_05.txt
./gen_random 6 > data/test_06.txt
./gen_random 7 > data/test_07.txt
./gen_random 8 > data/test_08.txt
./gen_random 9 > data/test_09.txt
./gen_random 10 > data/test_10.txt
```

> [!TIP]
> **Cách chạy tự động nhanh:**
> * Bạn có thể chạy nhanh 8 file ngẫu nhiên bằng vòng lặp Bash:
>   ```bash
>   for i in 03 04 05 06 07 08 09 10; do
>       ./gen_random $((10#$i)) > data/test_${i}.txt
>   done
>   ```
> * Hoặc chạy toàn bộ cả 10 file thông qua script [generate_all.sh](file:///d:/SORT%20Report/generate_all.sh):
>   ```bash
>   bash generate_all.sh
>   ```

---

### Bước 5: Thẩm định và kiểm tra tính toàn vẹn của dữ liệu

Sau khi tạo xong, bạn sử dụng các tiện ích Unix có sẵn trong MSYS2 để thẩm định kết quả:

#### 1. Kiểm tra kích thước và danh sách 10 file:
```bash
ls -lh data/
```
* **Kết quả kỳ vọng:** Đủ 10 file từ `test_01.txt` đến `test_10.txt`, mỗi file có dung lượng xấp xỉ **15 MB**.

#### 2. Kiểm tra số lượng dòng của mỗi file:
```bash
wc -l data/test_01.txt
```
* **Kết quả kỳ vọng:** Hiển thị đúng `1000001 data/test_01.txt` (gồm 1 dòng tiêu đề ghi $N = 1.000.000$ và $1.000.000$ dòng chứa số thực).

#### 3. Kiểm tra tính tăng dần của Dãy 1:
```bash
head -n 6 data/test_01.txt
tail -n 5 data/test_01.txt
```
* Dòng đầu là `1000000`.
* Các giá trị đầu nhỏ (ví dụ $\approx 1.97, 2.75...$) và các giá trị cuối lớn (ví dụ $\approx 999995.72, 999999.72...$).

#### 4. Kiểm tra tính giảm dần của Dãy 2:
```bash
head -n 6 data/test_02.txt
tail -n 5 data/test_02.txt
```
* Các giá trị đầu lớn ($\approx 999998...$) và các giá trị cuối nhỏ dần về $0$.

---

## 5. LỘ TRÌNH CÁC BƯỚC KẾ TIẾP

* **Bước 2: Cài đặt 4 thuật toán sắp xếp**
  * Cài đặt QuickSort (kỹ thuật chọn chốt trung vị 3 phần tử Median-of-Three để tránh lỗi Stack Overflow trên mảng tăng/giảm dần).
  * Cài đặt HeapSort (Max-Heap, hoán đổi tại chỗ, $O(1)$ không gian bộ nhớ phụ).
  * Cài đặt MergeSort (tối ưu hóa cấp phát mảng phụ).
  * Cài đặt chương trình gọi `std::sort` của C++ STL.
* **Bước 3: Biên dịch, chạy chương trình và tổng hợp kết quả**

  **3.1. Chuyển hướng đến thư mục chứa mã nguồn**
  * Mở terminal MSYS2 UCRT64.
  * Chuyển hướng đến thư mục `src`:
    ```bash
    cd "/d/SORT Report/src"
    ```

  **3.2. Biên dịch các thuật toán sắp xếp**
  * Sử dụng trình biên dịch `g++` với cờ tối ưu hóa `-O3` để biên dịch 4 chương trình:
    ```bash
    g++ -O3 heapsort.cpp -o heapsort.exe
    g++ -O3 quicksort.cpp -o quicksort.exe
    g++ -O3 mergesort.cpp -o mergesort.exe
    g++ -O3 sortC++.cpp -o sortC++.exe
    ```

  **3.3. Tạo thư mục chứa kết quả**
  * Tạo một thư mục `results` nằm cùng cấp với `src` để chứa file log:
    ```bash
    mkdir -p ../results
    ```

  **3.4. Chạy chương trình hàng loạt và tổng hợp**
  * Dùng vòng lặp Bash truyền 10 file trong thư mục `../data/` vào từng thuật toán, sau đó gom toàn bộ output ghi vào thư mục `../results/`:

  *Chạy HeapSort:*
  ```bash
  for f in ../data/test_*.txt; do
      echo "--- File: $f ---"
      ./heapsort.exe < "$f"
  done > ../results/ketqua_heapsort.txt
  ```

  *Chạy QuickSort:*
  ```bash
  for f in ../data/test_*.txt; do
      echo "--- File: $f ---"
      ./quicksort.exe < "$f"
  done > ../results/ketqua_quicksort.txt
  ```

  *Chạy MergeSort:*
  ```bash
  for f in ../data/test_*.txt; do
      echo "--- File: $f ---"
      ./mergesort.exe < "$f"
  done > ../results/ketqua_mergesort.txt
  ```

  *Chạy std::sort (C++):*
  ```bash
  for f in ../data/test_*.txt; do
      echo "--- File: $f ---"
      ./sortC++.exe < "$f"
  done > ../results/ketqua_sortC++.txt
  ```

* **Bước 4: Nhận xét và Kết luận (Dựa trên số liệu thực nghiệm)**

Dựa vào kết quả đo đạc thực tế trên 10 bộ dữ liệu (1.000.000 phần tử/bộ),em có rút ra các nhận xét sau:

1. **std::sort của C++ (Introsort):** Đạt hiệu năng tối ưu nhất toàn diện với thời gian trung bình chỉ **489.4 ms**. Thuật toán này là sự kết hợp thông minh giữa QuickSort, HeapSort (khi độ sâu đệ quy vượt ngưỡng) và Insertion Sort (khi mảng con nhỏ), giúp duy trì tốc độ cực nhanh mà không bao giờ rơi vào trường hợp xấu nhất $O(N^2)$.
2. **QuickSort (Randomized / Median-of-three):** Thể hiện tốc độ rất ấn tượng (trung bình **621.0 ms**). Đặc biệt trên Dãy 1 (tăng dần - 158.0 ms) và Dãy 2 (giảm dần - 270.0 ms), QuickSort chạy nhanh vượt trội nhờ kỹ thuật chọn chốt (pivot) tối ưu, tránh được hiện tượng phân chia lệch nghèo nàn.
3. **MergeSort:** Thời gian thực thi rất ổn định, dao động quanh mức 1540 - 1570 ms (trung bình **1468.1 ms**). Do bản chất Chia để trị, nó luôn thực hiện đủ số phép chia và trộn với độ phức tạp $O(N \log N)$ trong mọi trường hợp. Nhược điểm chính là tiêu tốn thêm không gian bộ nhớ phụ $O(N)$ để lưu mảng tạm thời khi trộn.
4. **HeapSort:** Có thời gian thực thi trung bình chậm nhất là **1701.3 ms**. Mặc dù đảm bảo độ phức tạp $O(N \log N)$ và không tốn bộ nhớ phụ $O(N)$ như MergeSort, HeapSort vẫn chậm hơn QuickSort và std::sort do các thao tác truy xuất phần tử trên cây Max-Heap có tính liên cục bộ bộ nhớ đệm (cache locality) kém hơn.
