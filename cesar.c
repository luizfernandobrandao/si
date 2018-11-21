#include <gtk/gtk.h>
#include <stdlib.h>

gchar *str;
GtkTextBuffer *buffer, *buffer2;
GtkTextIter iter, start, end;
GtkWidget *tview1, *tview2,  *entry;;

gchar * cesar(gchar *str, int tam, int chave) {
  
  gchar cifrada[tam];
  int enc;

  for(int i=0; i<tam; i++){
    enc = (int) str[i]-chave;
    str[i] = (char)enc;
  }
  return str;  
}

void button_clicked(GtkWidget *widget, gpointer data) {

  int tam, chave;
  gchar *cifrada;
  const gchar *schave;

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tview1));
  gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);
  str = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
  tam = strlen(str);
  schave = gtk_entry_get_text(GTK_ENTRY(entry));
  chave = atoi (schave);

  cifrada = cesar(str, tam, chave);

  buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tview2));
  gtk_text_buffer_get_iter_at_offset(buffer2, &iter, 0);
  gtk_text_buffer_insert(buffer2, &iter, cifrada, -1);

}

int main(int argc, char *argv[]) {
    
  GtkWidget *window;
  GtkWidget *fixed;

  GtkWidget *btn1;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);
  
  entry = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed), entry, 680, 160);
  gtk_entry_set_placeholder_text (GTK_ENTRY(entry), "Chave");

  btn1 = gtk_button_new_with_label("Descifrar");
  gtk_fixed_put(GTK_FIXED(fixed), btn1, 680, 200);
  gtk_widget_set_size_request(btn1, 80, 30);
  g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(button_clicked), NULL);

  tview1 = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(tview1), TRUE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(tview1), TRUE);
  gtk_fixed_put(GTK_FIXED(fixed), tview1, 50, 15);
  gtk_widget_set_size_request(tview1, 620, 220);

  tview2 = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(tview2), FALSE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(tview2), FALSE);
  gtk_fixed_put(GTK_FIXED(fixed), tview2, 50, 250);
  gtk_widget_set_size_request(tview2, 620, 220);

  g_signal_connect(G_OBJECT(window), "destroy", 
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
