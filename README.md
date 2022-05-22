# Bounty-Hunter
# Bài làm dự án cuối kỳ của Hoàng Hải Long

Sử dụng C/C++ và các thư viện [SDL2](https://www.libsdl.org/), [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/), [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/) và [SDL_image](https://www.libsdl.org/projects/SDL_image/)

## 1. Hướng dẫn cài đặt
- Chương trình sử dụng các file project của Code::Blocks.
- Hãy chắc chắn rằng bạn đã tải đầy đủ Code::Blocks, Mingw và các thư viện SDL2, SDL_image, SDL_ttf, SDL_mixer bản tương thích với thiết bị được sử dụng.
- Tải thư mục Bounty Hunter trong mục "Code" màu xanh lá, chọn "Download zip".
- Sửa lại đường dẫn vào file:
  - Nếu bạn chưa có sẵn các thư viện liên kết (các file .dll) trong system, hãy lấy chúng trong thư mục LibSdl2/Dll/x86 và paste chúng ra dự án chính
  - Nếu Code::Blocks của bạn chưa có đường dẫn đến các complier, hãy lấy chúng ở trong thư mục LibSdl2, phần include đã có đầy đủ 4 thư viện SDL2, SDL_mixer, SDL_ttf và SDL_image
  - Để chắc chắn, mở game.cbp bằng Code::Blocks, trong Project/Build options/Search directories/Compiler, xóa đường dẫn cũ và thay bằng các đường dẫn mới đến phần include của các thư mục nói trên, trong Linker xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục lib ứng với các thư viện trên.
  - Bên cạnh đó, hãy chắc chắn rằng phần Other linker options trong Project/Build options/Linker settings đã ghi đầy đủ: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
 - Chạy chương trình:
    - Chọn Build/Rebuild trên thanh điều khiển (hoặc ấn Ctrl-F11), nếu không thành công hãy thử khởi động lại Code::Blocks hoặc kiểm tra lại các thao tác.
    - Sau khi build thành công thì chương trình có thể chạy.
 - Lưu ý: Các tệp, thư mục nằm trong tệp WOLFLY bắt buộc phải có và không được thay đổi để chương trình không phát sinh lỗi khi chạy. Chức năng cụ thể đã được chú thích trong từng tệp.
 
 ## 2. Mô tả chung về trò chơi
 - Trong trò chơi, bạn nhập vai 1 thợ săn tiền thưởng, vượt qua các chướng ngại vật và quái vật để thu thập đủ 30 đồng vàng
 - Trên tay bạn chỉ duy nhất có một cây súng với đạn thường và đạn laser, với 3 mạng và 100 giây, hãy cố gắng vượt qua thử thách này

## 3. Mô tả các chức năng đã cài đặt
- 1. Màn hình menu:
  - Có 2 nút Play và Exit, nhấn Play để chơi và Exit để thoát
  <img src="https://drive.google.com/file/d/1EVkWl-oqFE7_jLb_7i1gYElaysgqspiE/view?usp=sharing">
- 2. Màn hình chơi:
  - Nhân vật chính, bản đồ và quái
  - Bắn trúng quái thì quái sẽ phát nổ
  - Chạm vào quái, đạn của quái hoặc rơi xuống vực sẽ mất 1 mạng
  - Có 3 nút bên dưới màn hình là pause, music và tutorial, từng phím sẽ cho chức năng tương ứng
  <img src="https://drive.google.com/file/d/1ecR3g2mkjVnbjdC4EOT-4SatbgU_-tWf/view?usp=sharing">
- 3. Màn hình pause
  - Có 2 nút là remuse để tiếp tục hoặc exit để thoát
- 4. Màn hình tutorial
  - Hiện ra hướng dẫn chơi game
  - Continue để tiếp tục
  <img src="https://drive.google.com/file/d/1Uddb9KkurYRgMYw0c8z-ZgrTPujF2QLe/view?usp=sharing">
- Link youtube : 

## 4. Các kỹ thuật lập trình được sử dụng trong chương trình:
- Đồ họa SDL
- Mảng
- Struct, Class
- Con trỏ
- Đọc file bằng ifstream
- Lập trình hướng đối tượng
- Kế thừa class

## 5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
- Dự án được hoàn thành là một bước tiến trong quá trình học tập của em, tự tay mình mày mò và fix lỗi đã giúp em học được nhiều điều và quan trọng nhất là vui mừng khi làm ra được một chương trình hoàn thiện đầu tiên
- Do thời gian có hạn, trò chơi vẫn còn nhiều điều thiếu sót, mong thầy cô đánh giá và góp ý. Về phần mình, em có khá nhiều dự định để phát triển game này như tạo thêm map mới, cái quái mơi, tạo boss, và thêm các chức năng như new game, điểm cao nhất, .... Sau này có thời gian em sẽ tiếp tục phát triển thêm
- Tuy rằng đây chỉ là một dự án lập trình đồ họa nhỏ, còn khá thô sơ và đơn giản, nhưng bản thân em đã học được rất nhiều điều. Thứ em tâm đắc nhất là sức mạnh của lập trình hướng đối tượng và tính kế thừa của class. Với chúng, những thứ tương tự nhau có thể định nghĩa dễ dàng từ một cấu trúc chung và những class tương tự nhau có thể kế thừa từ một class cha. Điều này tiết kiệm nhiều thời gian và công sức lập trình, và dễ hiểu cho cả người làm và người đọc. Bên cạnh đó, việc tiếp xúc với SDL đã giúp em có một cái nhìn rõ hơn về các chương trình, thay vì những dòng code và bài toán khô khan ở môn Nhập môn lập trình, nay em đã hiểu được cách phát triển một chương trình cơ bản, và cách biến những dòng code thành hình ảnh sinh động mà ai cũng có thể hiểu được.
- Cuối cùng em xin cảm ơn các thầy cô dạy lý thuyết, thực hành đã chỉ dạy và giúp em hoàn thành dự án này!
  
