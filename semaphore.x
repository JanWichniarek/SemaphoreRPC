program SEMAPHORE{
	version Remote{
		void up(int count)=1;
		void down(int count)=2;
	}=1;
}=0x20000000;