/*
Gabriel Casciano, COE628, Lab 9
500744076
*/
package lab9;

/**
 *
 * @author gabriel
 */
public class Lab99 {
    
    public static final int N = 5; // number of philosophers
    public enum state_t {EATING, THINKING, HUNGRY}; //differnt states a philosophers may be in
    public static Philosopher[] philosophers; //array of philosophers threads
    public static Semaphore forks; //the forks are a semaphore
    public static int counter = 0; //to keep track if the threads have all finished
    
    public static void main(String args[]){
        forks = new Semaphore(N); // init the semaphore
        philosophers = new Philosopher[N]; //init the philosophers array for size N
        
        //init each philosopher
        for(int i = 0; i < N; i++)
            philosophers[i] = new Philosopher(); 
        
        //start each philosopher
        for(int i = 0; i < N; i++)    
            philosophers[i].start();
        
        //wait for each philosopher to finish
        while(counter >= N);
       
        try{
                for(int i = 0; i < N; i++)
                    philosophers[i].join();
            }catch(Exception ex){
                System.out.println("Issue Dying");
            }

            System.out.println("We All Ate");
    }
    
    
    public static class Philosopher extends Thread{
        
        private static int MASTER_ID = 0;
        private int id = 0; // the id of the philosophers
        private state_t state; // the current state of philosophers
        private int L, R; // left and right neighbor
        
        public Philosopher(){
            this.id = MASTER_ID;
            MASTER_ID++;
            state = state_t.HUNGRY;
            if(this.id == 0){
                R = 1;
                L = N-1;
            }
            else if(this.id == N-1){
                R = 0;
                L = N-2;
            }
            else{
                R = this.id + 1;
                L = this.id - 1;
            }
        }
        
        //Custom toString()
        @Override
        public String toString(){ return "Phil: " + this.id + " State: " + this.state.toString(); }   
        
        /**
         * Thinking Function
         * philosophers thinks for 10 ms
         */
        public synchronized void thinking(){
            this.state = state_t.THINKING;
            System.out.println(this.toString());
            try{
                wait(10);// wait so wait can be interrupted by notify() or notifyAll()
            }
            catch(Exception ex){
                System.out.println("Failed to think");
            }
        }
        
        /**
         * Eating Function
         * philosophers eats for 15 ms
         */
        public synchronized void eating(){
            this.state = state_t.EATING;
            System.out.println(this.toString());
            try{
                Thread.sleep(15);// sleep so we are not interrupted by notify()
            }catch(Exception ex){
                System.out.println("Failed to eat");
            }
        }
        
         /**
         * takeForks Function
         * philosophers tries to take forks from the semaphore to eat
         */
        public synchronized void takeForks(){
            System.out.print(this.toString()); 
            System.out.print(" -- Trying to acquire forks ");
            //If the left or right neighbor are eating, we will think
            while(philosophers[L].getState_t() == state_t.EATING || philosophers[R].getState_t() == state_t.EATING){
                System.out.println(this.id + " -- Forks Busy");
                thinking();
            }
            
            //If our neighbours are not eating we will
            if(philosophers[L].getState_t() != state_t.EATING && philosophers[R].getState_t() != state_t.EATING){
                forks.down();
                forks.down();
                this.state = state_t.EATING;
                System.out.println(this.id + " -- Forks Acquired");
            }
            
                        
        }
        
        /**
         * putForks Function
         * philosophers returns forks to the semaphore and increases the counter
         */
        public synchronized void putForks(){
            this.state = state_t.THINKING;
            forks.up();
            forks.up();
            counter++;
        }
        
        //get function for state so we can check on our neighbours
        public state_t getState_t(){
            return this.state;
        }
        
        @Override
        public void run(){
            thinking();
            takeForks();
            eating();
            putForks();
            System.out.println(this.toString());
        }
    }
    
}
