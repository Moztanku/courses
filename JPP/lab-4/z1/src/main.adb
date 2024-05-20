with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;

procedure Main is
    Gen : Generator;

    type Fork is new Integer range 1 .. 100;
    type Philosopher is new Integer range Integer(Fork'First) .. Integer(Fork'Last);

    protected type Mutex is
        entry Pick;
        entry Put;
    private
        Available : Boolean := True;
    end Mutex;

    protected body Mutex is
        entry Pick when Available is
        begin
            Available := False;
        end Pick;
        entry Put when not Available is
        begin
            Available := True;
        end Put;
    end Mutex;

    Forks : array (Fork) of Mutex;

    task type Philosopher_Task (Id : Philosopher);
    task body Philosopher_Task is
        Lower, Higher : Fork;
        Hunger : Integer := 10;
    begin
        if Id = Philosopher'Last then
            Lower := Fork'First; Higher := Fork(Id);
        else
            Lower := Fork(Id); Higher := Fork(Id + 1);
        end if;

        loop
            Put_Line ("Philosopher" & Philosopher'Image (Id) & " is thinking");
            Thinking_delay : constant Duration := Duration (0.2 + 0.5 * Random(Gen));
            delay Thinking_delay;

            Forks (Lower).Pick;
            Forks (Higher).Pick;
            
            Put_Line ("Philosopher" & Philosopher'Image (Id) & " is eating");
            Eating_delay : constant Duration := Duration (0.2 + 1.0 * Random(Gen));
            delay Eating_delay;
            
            Forks (Lower).Put;
            Forks (Higher).Put;

            Hunger := Hunger - 1;
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
