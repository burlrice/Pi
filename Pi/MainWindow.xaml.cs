using System.Windows;

namespace Pi
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Update(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            var pi = Demo.Pi.Generate(100);
            System.Diagnostics.Trace.WriteLine($"[{pi.Length}] {pi}");
        }
    }
}
