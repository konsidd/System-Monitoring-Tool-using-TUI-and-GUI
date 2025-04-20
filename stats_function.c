void handle_error(char *message);
	/* Display error message and then terminate the program. */

void show_runtime_info();
 	/* Show how much memory the program use during the compilation. */

void show_memory_graph(double curr_use, double previous_use);
 	/* Using symbols representing the memory usage change.
	 	 Takes two doubles representing current and previous memory use,
		 and calculate the change based on the two inputs. */

void get_memory_info(long previous_use, int graph_flag);
 	/* Display both physical and virtual memory usage and the total memory.
		 If "--graphics" is called, virtualize the physical-use change. */

void calculate_cpu_use(int tdelay);
 	/* Calculate CPU usage (in percentage) in real-time.
 	   Takes an positive integer to indicate how long will it refresh. */

void show_cpu_graph(double percent);
 	/* Using "|" to represent the CPU usage change.
	 	 Takes a double representing the current CPU usage. */

void show_cpu_info(double cpu_use);
 	/* Prints the number of CPU cores and CPU usage percentage.
		 Takes a double representing the current CPU usage. */

void show_session_user();
 	/* Display user usage (username, terminal devices, IP address). */

void show_sys_info();
 	/* Display basic system information (OS name, release information,
 	   architecture, OS version, etc.). */