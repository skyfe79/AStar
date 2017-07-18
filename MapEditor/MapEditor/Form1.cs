using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;


namespace MapEditor
{
    public partial class frmMapEditor : Form
    {
        private int[,] mapData = null;
        private int row = 0;
        private int col = 0;
        private Size cellSize;
        private bool drag = false;
        private int curValue = 0;
        private Point oldStart = new Point(-1, -1);
        private Point oldGoal = new Point(-1, -1);
        public frmMapEditor()
        {
            InitializeComponent();
        }

        private void btnMakeMap_Click(object sender, EventArgs e)
        {
            if (txtRow.Text == "" || txtCol.Text == "")
            {
                MessageBox.Show("맵의 크기를 입력하세요.");
                return;
            }
            try
            {
                row = int.Parse(txtRow.Text);
                col = int.Parse(txtCol.Text);
                makeMap();
                txtRow.Enabled = false;
                txtCol.Enabled = false;
                btnMakeMap.Enabled = false;
            }
            catch (FormatException ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }


        }
        private void makeMap()
        {
            mapData = new int[row, col];
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    mapData[i, j] = 0;
                }
            }
            Invalidate();
        }
        private void drawMap(Graphics g)
        {
            Rectangle rect = new Rectangle(
                panel1.ClientRectangle.Width + 10,
                panel1.ClientRectangle.Y + 10,
                ClientRectangle.Width - panel1.ClientRectangle.Width - 20,
                ClientRectangle.Height - 20);

            cellSize.Width = rect.Width / col;
            cellSize.Height = rect.Height / row;

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    Rectangle cellRect = new Rectangle(
                        j * cellSize.Width + rect.X,
                        i * cellSize.Height + rect.Y,
                        cellSize.Width,
                        cellSize.Height);
                    if (mapData[i, j] == -1)
                    {
                        g.FillRectangle(new SolidBrush(Color.Red), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == -2)
                    {
                        g.FillRectangle(new SolidBrush(Color.Blue), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == 0)
                    {
                        g.FillRectangle(new SolidBrush(Color.White), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == 1)
                    {
                        g.FillRectangle(new SolidBrush(Color.LightGray), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == 2)
                    {
                        g.FillRectangle(new SolidBrush(Color.DarkGray), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == 3)
                    {
                        g.FillRectangle(new SolidBrush(Color.LightGreen), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == 4)
                    {
                        g.FillRectangle(new SolidBrush(Color.Gray), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                    if (mapData[i, j] == 5)
                    {
                        g.FillRectangle(new SolidBrush(Color.Black), cellRect);
                        g.DrawRectangle(new Pen(Color.Black), cellRect);
                    }
                }
            }
        }
        private Rectangle getCellRectangle(int r, int c)
        {
            Rectangle rect = new Rectangle(
               panel1.ClientRectangle.Width + 10,
               panel1.ClientRectangle.Y + 10,
               ClientRectangle.Width - panel1.ClientRectangle.Width - 20,
               ClientRectangle.Height - 20);
            Rectangle ret = new Rectangle(
                       c * cellSize.Width + rect.X,
                       r * cellSize.Height + rect.Y,
                       cellSize.Width,
                       cellSize.Height);
            return ret;
        }
        private Point getMapIndex(Point mouseCoord)
        {
            if (cellSize.Width <= 0)
                return new Point(0, 0);
            if (cellSize.Height <= 0)
                return new Point(0, 0);
            Point ret = new Point();
            ret.X = (mouseCoord.X - (panel1.Width + 10)) / cellSize.Width;
            ret.Y = (mouseCoord.Y - 10) / cellSize.Height;

            return ret;
        }
        private void clear()
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    mapData[i, j] = 0;
                }
            }
        }
        private void init()
        {
            drag = false;
            curValue = 0;
        }
        private void frmMapEditor_Paint(object sender, PaintEventArgs e)
        {
            if (row == 0 && col == 0)
                return;
            drawMap(e.Graphics);
        }

        private void frmMapEditor_Resize(object sender, EventArgs e)
        {
            Invalidate();
        }
        
        private void frmMapEditor_MouseDown(object sender, MouseEventArgs e)
        {
            if (mapData == null)
                return;
            drag = true;
            Point RowCol = getMapIndex(e.Location);
            if (RowCol.X < 0 || RowCol.X >= col)
                return;
            if (RowCol.Y < 0 || RowCol.Y >= row)
                return;
            if (curValue == -1)
            {
                if (oldStart != new Point(-1, -1))
                {
                    mapData[oldStart.Y, oldStart.X] = 0;
                    Invalidate(getCellRectangle(oldStart.Y, oldStart.X), false);
                }
                oldStart = RowCol;
            }
            if (curValue == -2)
            {
                if (oldGoal != new Point(-1, -1))
                {
                    mapData[oldGoal.Y, oldGoal.X] = 0;
                    Invalidate(getCellRectangle(oldGoal.Y, oldGoal.X), false);
                }
                oldGoal = RowCol;
            }
            mapData[RowCol.Y, RowCol.X] = curValue;
            Invalidate(getCellRectangle(RowCol.Y, RowCol.X), false);
        }

        private void frmMapEditor_MouseMove(object sender, MouseEventArgs e)
        {
            if (mapData == null)
                return;

            if (drag)
            {
                Point RowCol = getMapIndex(e.Location);
                if (RowCol.X < 0 || RowCol.X >= col)
                    return;
                if (RowCol.Y < 0 || RowCol.Y >= row)
                    return;
                if (curValue == -1)
                {
                    if (oldStart != new Point(-1, -1))
                    {
                        mapData[oldStart.Y, oldStart.X] = 0;
                        Invalidate(getCellRectangle(oldStart.Y, oldStart.X), false);
                    }
                    oldStart = RowCol;
                }
                if (curValue == -2)
                {
                    if (oldGoal != new Point(-1, -1))
                    {
                        mapData[oldGoal.Y, oldGoal.X] = 0;
                        Invalidate(getCellRectangle(oldGoal.Y, oldGoal.X), false);
                    }
                    oldGoal = RowCol;
                }
                mapData[RowCol.Y, RowCol.X] = curValue;
                Invalidate(getCellRectangle(RowCol.Y, RowCol.X), false);
            }
        }

        private void frmMapEditor_MouseUp(object sender, MouseEventArgs e)
        {
            if (mapData == null)
                return;

            drag = false;
            Point RowCol = getMapIndex(e.Location);
            if (RowCol.X < 0 || RowCol.X >= col)
                return;
            if (RowCol.Y < 0 || RowCol.Y >= row)
                return;
            if (curValue == -1)
            {
                if (oldStart != new Point(-1, -1))
                {
                    mapData[oldStart.Y, oldStart.X] = 0;
                    Invalidate(getCellRectangle(oldStart.Y, oldStart.X), false);
                }
                oldStart = RowCol;
            }
            if (curValue == -2)
            {
                if (oldGoal != new Point(-1, -1))
                {
                    mapData[oldGoal.Y, oldGoal.X] = 0;
                    Invalidate(getCellRectangle(oldGoal.Y, oldGoal.X), false);
                }
                oldGoal = RowCol;
            }
            mapData[RowCol.Y, RowCol.X] = curValue;
            Invalidate(getCellRectangle(RowCol.Y, RowCol.X), false);
        }

       
        private void button4_Click(object sender, EventArgs e)
        {
            curValue = -1;
            label3.Text = "START";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            curValue = -2;
            label3.Text = "GOAL";
        }

        private void button6_Click(object sender, EventArgs e)
        {
            curValue = 0;
            label3.Text = "길(0)";
        }

        private void button7_Click(object sender, EventArgs e)
        {
            curValue = 1;
            label3.Text = "길(1)";
        }

        private void button8_Click(object sender, EventArgs e)
        {
            curValue = 2;
            label3.Text = "길(2)";
        }

        private void button9_Click(object sender, EventArgs e)
        {
            curValue = 3;
            label3.Text = "길(3)";
        }

        private void button10_Click(object sender, EventArgs e)
        {
            curValue = 4;
            label3.Text = "길(4)";
        }

        private void button11_Click(object sender, EventArgs e)
        {
            curValue = 5;
            label3.Text = "장애물(5)";
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            txtRow.Enabled = true;
            txtCol.Enabled = true;
            btnMakeMap.Enabled = true;
            clear();
        }

        private void btnSaveMap_Click(object sender, EventArgs e)
        {
            if (mapData == null)
                return;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(saveFileDialog1.FileName,
                    FileMode.Create, FileAccess.Write);
                BinaryWriter binW = new BinaryWriter(fs);
                binW.Write(row);
                binW.Write(col);
             
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        binW.Write(mapData[i, j]);
                    }
                }
                binW.Close();

            }
        }

        private void btnLoadMap_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(openFileDialog1.FileName,
                    FileMode.Open, FileAccess.Read);
                BinaryReader binR = new BinaryReader(fs);
                row = binR.ReadInt32();
                col = binR.ReadInt32();
                mapData = new int[row, col];
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        mapData[i, j] = binR.ReadInt32();
                        if (mapData[i, j] == -1)
                        {
                            oldStart = new Point(i, j);
                        }
                        if (mapData[i, j] == -2)
                        {
                            oldGoal = new Point(i, j);
                        }
                    }
                }
                binR.Close();
                init();
                txtRow.Text = row.ToString();
                txtCol.Text = col.ToString();
                Invalidate();
            }
        }
    }
}
