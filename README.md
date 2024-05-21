# Bài tập lớn: Game - Space-Shooter # (INT2215-2024)
Đây là một tựa game shoot em up (hay còn gọi là bắn may bay) khá đơn giản, có tham khảo trên trang UK Parallel (trang hướng dẫn làm game).

## Mô tả về các đối tượng trong trò chơi

- *Shooter* là nhân vật chính của trò chơi. Shooter có thể di chuyển theo 4 hướng trái/phải/lên/xuống hoặc theo góc chéo theo sự điều khiển của người chơi.
- *Enemy* là các đối tượng mà Shooter phải tiêu diệt. Enemy xuất hiện ngẫu nhiên và có tốc độ di chuyển ngẫu nhiêu. Khi bị tiêu diệt Enemy sẽ sinh ra Point để Shooter thu thập.
- *Bullet* là đối tượng mà cả Shooter và Enemy đều có thể bắn ra. Shooter có thể bắn Bullet liên tục bằng nút SHIFT, còn Enemy bắn Bullet với rate ngẫu nhiên. Bullet của Enemy luôn bay theo hướng về vị trí hiện tại của Shooter.
- *Bullet* là đối tượng mà Enemy sẽ sinh ra khi bị tiêu diệt. Người chơi cần phải thu thập Point để có thể tăng điểm. Point sẽ di chuyển theo hướng ngẫu nhiên và nảy lại nếu chạm phải rìa màn hình của trò chơi. Point có thời gian sống giới hạn (2 giây) và sẽ biến mất nếu Shooter không kịp thu thập.

## Mô tả game play
- Trước lần đầu chơi game sẽ có một người hiện lên và nói Chúc may mắn (trong 2 giây), người này sẽ không xuất hiện vào những lần chơi sau (trừ khi thoát khỏi chương trình rồi chạy lại).
- Di chuyển Shooter bằng các nút mũi tên ↑↓←→ và bắn đạn bằng nút SHIFT.
- Trong một màn chơi, Shooter sẽ được người chơi di chuyển, bắn hạ kẻ địch, đồng thời né đạn và thu thập điểm với mục tiêu là đạt số điểm cao nhất có thể.
- Shooter sẽ bị giết khi va chạm với Enemy hoặc bị trúng đạn của Enemy. Lúc đấy trò chơi kết thúc.
- Enemy bị tiêu diệt khi trúng đạn của player.
- Sau khi Player chết sẽ hiện lên điểm của màn chơi và highscore. Highscore sẽ tự động reset về 0 khi chương trình kết thúc (không lưu cho lần tiếp theo mở chương trình).
- Ấn SPACE để dừng / tiếp tục chơi

## Các kĩ năng áp dụng trong code game
- Quản lí objects bằng linked list (chủ yếu là thêm và xoá các items khỏi linked list), xử lý đạn bắn bằng linked list
- Collision detection
- Slope calculation: áp dụng để đạn của kẻ địch luôn bắn vào vị trí người chơi
- Đồ họa, âm thanh và texting sử dụng thư viện SDL2_image, SDL2_mixer và SDL2_ttf
- Cách tạo một game đơn giản: handle events, handle keyboard input, tạo game loop, tạo game pause, capture time frame, etc.
- Cách dùng hàm random khiến những objects (enemy, đạn mà enemy bắn ra, tốc độ của enemy và đạn của enemy) xuất hiện một cách ngẫu nhiên
- Cách debug (dùng cerr, in ra kết quả từng bước trong một file để xem chương trình đã chạy sai phần nào, etc.)

## Các tính năng có thể cải thiện:
- Chọn player
- Chọn background
- Thêm power up cho player, Enemy boss

## Điểm hạn chế của Game
- Lỗi rò rỉ bộ nhớ (theo em phỏng đoán là tạo con trỏ nhưng chưa xoá)

## Ngưỡng điểm mong muốn: 7.5 - 8.5

## Nguồn tham khảo
- Game: https://www.parallelrealities.co.uk/tutorials/shooter/shooter1.php, https://www.youtube.com/watch?v=mrsT_WofAQ0
- SDL2: https://www.youtube.com/watch?v=QM4WW8hcsPU&list=PLvv0ScY6vfd-p1gSnbQhY7vMe2rng0IL0, https://lazyfoo.net/tutorials/SDL/index.php, https://wiki.libsdl.org/wiki/index (bao gồm cả SDL2_image, SDL2_mixer và SDL2_ttf)
