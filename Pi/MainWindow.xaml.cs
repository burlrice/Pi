using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Text.RegularExpressions;
using System.Windows.Input;
using System;

namespace Pi
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        Dictionary<string, List<string>> fonts { get; set; } = Demo.FreeType.Fonts;
        public List<string> Fonts => fonts.Select(f => f.Key).ToList().OrderBy(s => s).ToList();
        public List<string> Styles { get; set; } = new List<string>();
        public int FontHeight { get; set; } = 30;
        public string RenderedString { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        public MainWindow()
        {
            InitializeComponent();
            FontNamesComboBox.SelectedItem = Fonts.Where(f => f == "Microsoft Sans Serif").FirstOrDefault();
            PropertyChanged(this, new PropertyChangedEventArgs(nameof(Fonts)));
        }

        private void Update(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            int n;

            if (Int32.TryParse((sender as System.Windows.Controls.TextBox).Text, out n))
            {
                FontHeight = n;
                Update();
            }
        }

        private void Update()
        {
            RenderedString = Demo.FreeType.RenderChar(
                FontNamesComboBox.SelectedItem as string, 
                FontStylesComboBox.SelectedItem as string, 
                FontHeight, 
                new string("π"));
            PropertyChanged(this, new PropertyChangedEventArgs(nameof(RenderedString)));            
        }

        private void FontName_Selected(object sender, RoutedEventArgs e)
        {
            var selected = FontStylesComboBox.SelectedItem as string;

            Styles = fonts[FontNamesComboBox.SelectedItem as string].ToList();
            PropertyChanged(this, new PropertyChangedEventArgs(nameof(Styles)));
            FontStylesComboBox.SelectedItem = Styles.Contains(selected) ? selected : Styles.FirstOrDefault();
            Update();
        }

        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            e.Handled = new Regex("[^0-9]+").IsMatch(e.Text);

            if (e.Handled)
            {
                Update();
            }
        }

        private void FontStyle_Selected(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            Update();
        }
    }
}
