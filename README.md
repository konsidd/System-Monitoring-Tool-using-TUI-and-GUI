# System Monitoring Tool using TUI and GUI
 
SysWatch - System Monitoring Tool
SysWatch is a lightweight system monitoring tool built in C that runs in three modes:
- CLI Mode: Command-line based with argument support and optional logging
- TUI Mode: Terminal-based UI with live updating bars (like htop)
- GUI Mode: GTK-based graphical interface


🚀 Features
- Live monitoring of CPU and memory usage
- Text-based visualization (TUI)
- GTK GUI interface with real-time updates
- Signal handling for safe termination
- Logging support
- Easy to build and install


📦 Dependencies
For All Modes:
•	- gcc
For TUI (Terminal UI):
sudo apt install libncurses5-dev
For GUI (Graphical UI):
sudo apt install libgtk-3-dev


🛠 Build Instructions
Clone or download the project files, then run:
make
make install

To build TUI mode:
gcc tui_syswatch.c -o syswatch-tui -lncurses
To build GUI mode:
gcc gui_syswatch.c -o syswatch-gui `pkg-config --cflags --libs gtk+-3.0`


📈 How to Use
CLI Mode:
./syswatch --samples 5 --tdelay 1 --graphics --logfile stats.txt
Options:
- --samples N         → Number of samples to collect
- --tdelay N          → Delay in seconds between each sample
- --graphics          → Show usage as text bars
- --logfile filename  → Save output to a log file
- --help              → Show usage instructions


TUI Mode:
./syswatch-tui
Displays CPU and memory usage as progress bars. Press 'q' to quit.
GUI Mode:
./syswatch-gui
Launches a window showing CPU and memory stats updated every second.


📁 Project Structure
syswatch/
├── main.c               # CLI mode
├── tui_syswatch.c       # TUI mode (ncurses)
├── gui_syswatch.c       # GUI mode (GTK)
├── stats_function.c     # System data logic
├── stats_function.h
├── Makefile
└── README.md

💡 Future Enhancements
- Real process tracking
- Export data to CSV or JSON
- Background daemon mode
- Network and disk monitoring
- Unified binary for all modes

- 
🧑‍💻 Author
Built with ❤️ for system geeks who love clean, fast, native C apps.


📜 License
MIT License. Free to use and modify!
