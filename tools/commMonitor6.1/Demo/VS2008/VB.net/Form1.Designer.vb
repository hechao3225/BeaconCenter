<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.splitter1 = New System.Windows.Forms.Splitter
        Me.redtData = New System.Windows.Forms.RichTextBox
        Me.ctlData = New System.Windows.Forms.RichTextBox
        Me.comboBox1 = New System.Windows.Forms.ComboBox
        Me.button1 = New System.Windows.Forms.Button
        Me.button4 = New System.Windows.Forms.Button
        Me.btnPause = New System.Windows.Forms.Button
        Me.btnOpen = New System.Windows.Forms.Button
        Me.btnClear = New System.Windows.Forms.Button
        Me.statusStrip1 = New System.Windows.Forms.StatusStrip
        Me.lblTip = New System.Windows.Forms.ToolStripStatusLabel
        Me.toolStripStatusLabel4 = New System.Windows.Forms.ToolStripStatusLabel
        Me.toolStripStatusLabel1 = New System.Windows.Forms.ToolStripStatusLabel
        Me.AxCommMonitor1 = New AxCommMonitor6x.AxCommMonitor
        Me.statusStrip1.SuspendLayout()
        CType(Me.AxCommMonitor1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'splitter1
        '
        Me.splitter1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.splitter1.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.splitter1.Location = New System.Drawing.Point(0, 318)
        Me.splitter1.Name = "splitter1"
        Me.splitter1.Size = New System.Drawing.Size(785, 5)
        Me.splitter1.TabIndex = 11
        Me.splitter1.TabStop = False
        '
        'redtData
        '
        Me.redtData.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.redtData.Dock = System.Windows.Forms.DockStyle.Fill
        Me.redtData.Location = New System.Drawing.Point(0, 42)
        Me.redtData.Name = "redtData"
        Me.redtData.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical
        Me.redtData.Size = New System.Drawing.Size(785, 281)
        Me.redtData.TabIndex = 9
        Me.redtData.Text = ""
        '
        'ctlData
        '
        Me.ctlData.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.ctlData.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.ctlData.Location = New System.Drawing.Point(0, 323)
        Me.ctlData.Name = "ctlData"
        Me.ctlData.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical
        Me.ctlData.Size = New System.Drawing.Size(785, 210)
        Me.ctlData.TabIndex = 10
        Me.ctlData.Text = ""
        '
        'comboBox1
        '
        Me.comboBox1.FormattingEnabled = True
        Me.comboBox1.Items.AddRange(New Object() {"COM1", "COM2", "COM3", "COM4", "COM5", "COM6"})
        Me.comboBox1.Location = New System.Drawing.Point(226, 16)
        Me.comboBox1.Name = "comboBox1"
        Me.comboBox1.Size = New System.Drawing.Size(45, 20)
        Me.comboBox1.TabIndex = 26
        Me.comboBox1.Text = "COM1"
        '
        'button1
        '
        Me.button1.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.button1.Location = New System.Drawing.Point(621, 13)
        Me.button1.Name = "button1"
        Me.button1.Size = New System.Drawing.Size(75, 23)
        Me.button1.TabIndex = 25
        Me.button1.Text = "ABout"
        Me.button1.UseVisualStyleBackColor = True
        '
        'button4
        '
        Me.button4.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.button4.Location = New System.Drawing.Point(702, 13)
        Me.button4.Name = "button4"
        Me.button4.Size = New System.Drawing.Size(75, 23)
        Me.button4.TabIndex = 24
        Me.button4.Text = "Close"
        Me.button4.UseVisualStyleBackColor = True
        '
        'btnPause
        '
        Me.btnPause.Location = New System.Drawing.Point(387, 13)
        Me.btnPause.Name = "btnPause"
        Me.btnPause.Size = New System.Drawing.Size(93, 23)
        Me.btnPause.TabIndex = 23
        Me.btnPause.Text = "Pause"
        Me.btnPause.UseVisualStyleBackColor = True
        '
        'btnOpen
        '
        Me.btnOpen.ForeColor = System.Drawing.Color.Black
        Me.btnOpen.Location = New System.Drawing.Point(277, 13)
        Me.btnOpen.Name = "btnOpen"
        Me.btnOpen.Size = New System.Drawing.Size(104, 23)
        Me.btnOpen.TabIndex = 22
        Me.btnOpen.Text = "Start Monitor"
        Me.btnOpen.UseVisualStyleBackColor = True
        '
        'btnClear
        '
        Me.btnClear.Location = New System.Drawing.Point(516, 13)
        Me.btnClear.Name = "btnClear"
        Me.btnClear.Size = New System.Drawing.Size(75, 23)
        Me.btnClear.TabIndex = 21
        Me.btnClear.Text = "Clear"
        Me.btnClear.UseVisualStyleBackColor = True
        '
        'statusStrip1
        '
        Me.statusStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.lblTip, Me.toolStripStatusLabel4, Me.toolStripStatusLabel1})
        Me.statusStrip1.Location = New System.Drawing.Point(0, 533)
        Me.statusStrip1.Name = "statusStrip1"
        Me.statusStrip1.Size = New System.Drawing.Size(785, 22)
        Me.statusStrip1.TabIndex = 27
        Me.statusStrip1.Text = "statusStrip1"
        '
        'lblTip
        '
        Me.lblTip.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) _
                    Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) _
                    Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
        Me.lblTip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
        Me.lblTip.Name = "lblTip"
        Me.lblTip.Size = New System.Drawing.Size(385, 17)
        Me.lblTip.Spring = True
        '
        'toolStripStatusLabel4
        '
        Me.toolStripStatusLabel4.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) _
                    Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) _
                    Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
        Me.toolStripStatusLabel4.IsLink = True
        Me.toolStripStatusLabel4.Name = "toolStripStatusLabel4"
        Me.toolStripStatusLabel4.Size = New System.Drawing.Size(385, 17)
        Me.toolStripStatusLabel4.Spring = True
        '
        'toolStripStatusLabel1
        '
        Me.toolStripStatusLabel1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.None
        Me.toolStripStatusLabel1.Name = "toolStripStatusLabel1"
        Me.toolStripStatusLabel1.Size = New System.Drawing.Size(0, 17)
        Me.toolStripStatusLabel1.Text = "toolStripStatusLabel1"
        '
        'AxCommMonitor1
        '
        Me.AxCommMonitor1.Dock = System.Windows.Forms.DockStyle.Top
        Me.AxCommMonitor1.Location = New System.Drawing.Point(0, 0)
        Me.AxCommMonitor1.Name = "AxCommMonitor1"
        Me.AxCommMonitor1.OcxState = CType(resources.GetObject("AxCommMonitor1.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxCommMonitor1.Size = New System.Drawing.Size(785, 42)
        Me.AxCommMonitor1.TabIndex = 0
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(785, 555)
        Me.Controls.Add(Me.comboBox1)
        Me.Controls.Add(Me.button1)
        Me.Controls.Add(Me.button4)
        Me.Controls.Add(Me.btnPause)
        Me.Controls.Add(Me.btnOpen)
        Me.Controls.Add(Me.btnClear)
        Me.Controls.Add(Me.splitter1)
        Me.Controls.Add(Me.redtData)
        Me.Controls.Add(Me.ctlData)
        Me.Controls.Add(Me.AxCommMonitor1)
        Me.Controls.Add(Me.statusStrip1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.statusStrip1.ResumeLayout(False)
        Me.statusStrip1.PerformLayout()
        CType(Me.AxCommMonitor1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents AxCommMonitor1 As AxCommMonitor6x.AxCommMonitor
    Private WithEvents splitter1 As System.Windows.Forms.Splitter
    Private WithEvents redtData As System.Windows.Forms.RichTextBox
    Private WithEvents ctlData As System.Windows.Forms.RichTextBox
    Private WithEvents comboBox1 As System.Windows.Forms.ComboBox
    Private WithEvents button1 As System.Windows.Forms.Button
    Private WithEvents button4 As System.Windows.Forms.Button
    Private WithEvents btnPause As System.Windows.Forms.Button
    Private WithEvents btnOpen As System.Windows.Forms.Button
    Private WithEvents btnClear As System.Windows.Forms.Button
    Private WithEvents statusStrip1 As System.Windows.Forms.StatusStrip
    Private WithEvents lblTip As System.Windows.Forms.ToolStripStatusLabel
    Private WithEvents toolStripStatusLabel4 As System.Windows.Forms.ToolStripStatusLabel
    Private WithEvents toolStripStatusLabel1 As System.Windows.Forms.ToolStripStatusLabel

End Class
