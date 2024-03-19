namespace Galois
{
    public struct Order1234577
    {
        public const int value = 1234577;
    }

    public class Field<T> : IComparable<Field<T>> where T : struct
    {
        public const int order = Order1234577.value;

        public Field(int value)
        {
            m_value = value % order;
        }

        public void set(Field<T> value)
        {
            m_value = value.m_value;
        }

        public override string ToString()
        {
            return m_value.ToString();
        }
        public int CompareTo(Field<T>? other)
        {
            if (other == null)
                return 1;
            if (this.m_value < other.m_value)
                return -1;
            else if (this.m_value > other.m_value)
                return 1;
            else
                return 0;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;

            Field<T> other = (Field<T>)obj;
            return m_value == other.m_value;
        }

        public override int GetHashCode()
        {
            return m_value.GetHashCode();
        }

        public static Field<T> operator +(Field<T> a, Field<T> b)
        {
            return new Field<T>(a.m_value + b.m_value % order);
        }

        public static Field<T> operator -(Field<T> a, Field<T> b)
        {
            Field<T> inverse = -b;
            return a + inverse;
        }

        public static Field<T> operator *(Field<T> a, Field<T> b)
        {
            return new Field<T>(a.m_value * b.m_value % order);
        }

        public static Field<T> operator /(Field<T> a, Field<T> b)
        {
            Field<T> inverse = ~b;
            return a * inverse;
        }

        public static Field<T> operator -(Field<T> a)
        {
            return new Field<T>(order - a.m_value);
        }

        public static Field<T> operator ~(Field<T> a)
        {
            return new Field<T>(egcd(a.m_value));
        }
        private int m_value;

        private static int egcd(int a)
        {
            int b = order;

            int x = 1, y = 0;
            int x1 = 0, y1 = 1;

            while (b != 0)
            {
                int q = a / b;

                int x2 = x - q * x1;
                int y2 = y - q * y1;
                int c = a - q * b;

                x = x1;
                y = y1;
                a = b;

                x1 = x2;
                y1 = y2;
                b = c;
            }

            if (x < 0)
                x += order;

            return x;
        }
    }
}