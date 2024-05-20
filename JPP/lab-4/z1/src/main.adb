with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;

procedure Main is
    Gen : Generator;

    type Fork is new Integer range 1 .. 100;
    type Philosopher is new Integer range Integer(Fork'First) .. Integer(Fork'Last);

    protected type Semaphore is
        entry P;
        entry V;
    private
        Available : Boolean := True;
    end Semaphore;

    protected body Semaphore is
        entry P when Available is
        begin
            Available := False;
        end P;
        entry V when not Available is
        begin
            Available := True;
        end V;
    end Semaphore;

    Forks : array (Fork) of Semaphore;

    task type Philosopher_Task (Id : Philosopher);
    task body Philosopher_Task is
        Left, Right : Fork;
        Hunger : Integer := 10;
    begin
        if Id = Philosopher'Last then
            Left := Fork'First; Right := Fork(Id);
        else
            Left := Fork(Id); Right := Fork(Id + 1);
        end if;
        loop
            Put_Line ("Philosopher" & Philosopher'Image (Id) & " is thinking");
            Thinking_delay : constant Duration := Duration (0.2 + 0.5 * Random(Gen));
            delay Thinking_delay;
            Forks (Left).P;
            Forks (Right).P;
            
            Put_Line ("Philosopher" & Philosopher'Image (Id) & " is eating");
            Eating_delay : constant Duration := Duration (0.2 + 1.0 * Random(Gen));
            delay Eating_delay;
            Hunger := Hunger - 1;
            Forks (Left).V;
            Forks (Right).V;

            if Hunger = 0 then
                Put_Line ("Philosopher" & Philosopher'Image (Id) & " is done");
                exit;
            end if;
        end loop;
    end Philosopher_Task;

    type Philosopher_Task_Access is access all Philosopher_Task;
    Philosophers : array (Philosopher) of Philosopher_Task_Access;
begin
    Reset (Gen);

    for P in Philosopher loop
        Philosophers(P) := new Philosopher_Task(Id => P);
    end loop;
end Main;
