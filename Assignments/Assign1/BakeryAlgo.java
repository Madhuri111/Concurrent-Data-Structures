public class BakeryAlgo extends Thread {

	//Initially,declared 5 threads
	public static final int totalThreads=5;

	//As by the algorthim,holder with smallest ticket can enter first into critical section
	//So assigning a ticket for each thread
	//Used static volatile so that irrespective of any thread or where they are,everyone can access these arrays
	private static volatile int[] tickets=new int[totalThreads]; 

	//this array is to check whether it is in critical section or not
	private static volatile boolean[] choosing=new boolean[totalThreads]; 
	// Variables for the threads. 
	public int thread_id; // The id of the current thread.

	//this variable is common for all threads which can enter into critical section
	public static volatile int count = 0; 

	public BakeryAlgo (int number)
	{
		//assigning a value for ticket
		thread_id=number;
	}

	//Functions lock,unlock while operating with Critical Section
	public void lock(int number)
	{
		
		choosing[number] = true;

		// Find the max value and add 1 to get the next available ticket.
		int m = tickets[0];
		for (int i = 0; i < tickets.length; ++i) { 
				if (tickets[i] > m)
					m = tickets[i];
			}
		// Allotting a new ticket value as MAXIMUM + 1 
		tickets[number] = m + 1;
		choosing[number] = false;
		// The ENTRY Section starts from here 
		for (int other = 0; other < totalThreads; ++other) { 

			// Applying the bakery algorithm conditions 
			while (choosing[other]) { 
			}
			while (tickets[other] != 0 && (tickets[other] 
											< tickets[number] 
										|| (tickets[other] 
												== tickets[number] 
											&& other < number))) { 
			} 
		} 
	}
	public void unlock(int number)
	{	
		tickets[number]=0;
	}

	// Simple test of a global counter. 
	public void run() {
		int scale = 2;

		for (int i = 0; i < totalThreads; i++) {

			lock(thread_id);
				// Start of critical section.
				count = count + 1;
				System.out.println("I am " + thread_id + " and count is: " + count);
				
				// Wait, in order to cause a race condition among the threads.
				try {
					sleep((int) (Math.random() * scale));
				} catch (InterruptedException e) { /* nothing */ }
				// End of critical section.
			unlock(thread_id);
			
		} // for

	}

	//main function for creating and executing threads
	public static void main(String[] args) 
	{ 

		//Initializing everything to zero and false
		for (int i = 0; i < totalThreads; ++i) { 
			choosing[i]=false;
			tickets[i]=0;
		}

		// Declaring the thread variables 
		BakeryAlgo[] threads_create=new BakeryAlgo[totalThreads]; 

		for (int i = 0; i < totalThreads; ++i) { 

			// Creating a new thread with the function 
			threads_create[i]=new BakeryAlgo(i);
			//starting thread
			threads_create[i].start();
		} 

		for (int i = 0; i < totalThreads; ++i) { 

			// Reaping the resources used by 
			// all threads once their task is completed ! 
			try{
			threads_create[i].join();
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
		} 

	}
}



 
