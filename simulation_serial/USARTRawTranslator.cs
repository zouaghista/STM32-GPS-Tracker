
using (StreamWriter writer = new StreamWriter(@"C:\Users\MOHAMED\Desktop\TP Damergi\Tramsim3.ini"))
{
    writer.WriteLine("signal void push(void)  {\r\n  PORTC &= ~0x002000;\r\n  swatch (0.05);\r\n  PORTC |= 0x002000;\r\n}\r\n");
    writer.WriteLine("signal void send_line (void) {\nwhile(1){");
    Stream s = new FileStream(@"C:\Users\MOHAMED\Desktop\TP Damergi\test2.txt", FileMode.Open);
    int val = 0;
    int counter = 0;
    char ch;
    while (true)
    {
        val = s.ReadByte();

        if (val < 0)
            break;
        writer.WriteLine("swatch(0.01);");
        ch = (char)val;
        if (ch == '\n')
        {
            writer.WriteLine(@"S1IN='\n';");
        }
        else if (ch == '\r')
        {
            writer.WriteLine(@"S1IN='\r';");
        }
        else
        {
            writer.WriteLine("S1IN='" + ch + "';");
        }
        if (counter > 2000) 
        {
            break;
        }
        counter++;
        Console.Write(ch);
    }
    writer.WriteLine("}}");
}