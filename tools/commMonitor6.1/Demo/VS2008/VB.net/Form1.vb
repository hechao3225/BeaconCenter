Public Class Form1

    Private Sub button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles button4.Click
        Me.Close()
    End Sub

    Private Sub button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles button1.Click
        Me.AxCommMonitor1.AboutBox()
    End Sub

    Private Sub btnClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClear.Click
        Me.redtData.Clear()
        Me.ctlData.Clear()
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.Text = AxCommMonitor1.Caption + " FOR VS2008 VB.net DEMO"
    End Sub

    Dim fPause As Boolean = False
    Dim fActive As Boolean = False
    Dim dwReadTotal As Long = 0
    Dim dwWriteTotal As Long = 0

    Private Sub btnPause_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnPause.Click
        If AxCommMonitor1.PauseMonitor(fPause) Then
            fPause = Not fPause
        End If

        If (fPause) Then
            btnPause.Text = "Continue"
            btnPause.ForeColor = Color.Black
        Else
            btnPause.Text = "Pause"
            btnPause.ForeColor = Color.Blue
        End If
    End Sub

    Private Sub btnOpen_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnOpen.Click
        If (fActive = False) Then
            fActive = AxCommMonitor1.StartMonitor(comboBox1.Text)
        Else
            AxCommMonitor1.StopMonitor()
            fActive = False
        End If

        If (fActive = True) Then
            btnOpen.Text = "Stop Monitor"
            btnOpen.ForeColor = Color.Blue

        Else
            btnOpen.Text = "Start Monitor"
            btnOpen.ForeColor = Color.Black
        End If
    End Sub

    Private Sub AxCommMonitor1_OnAscii(ByVal sender As System.Object, ByVal e As AxCommMonitor6x.ICommMonitor6Events_OnAsciiEvent) Handles AxCommMonitor1.OnAscii
        Const IRP_MJ_CREATE As Integer = &H0
        Const IRP_MJ_CLOSE As Integer = &H2
        Const IRP_MJ_READ As Integer = &H3
        Const IRP_MJ_WRITE As Integer = &H4
        Const IRP_MJ_DEVICE_CONTROL As Integer = &HE
        Const IRP_MJ_CLEANUP As Integer = &H12
        Const IRP_MJ_MAXIMUM_FUNCTION As Integer = &H1B
        Const IRP_MJ_FLUSH_BUFFERS As Integer = &H9

        Select (e.dwCtrlCode)
            Case IRP_MJ_CLOSE
                redtData.AppendText(String.Format("{0}: Close" + vbCrLf, e.sPortName))
            Case IRP_MJ_CREATE
                redtData.AppendText(String.Format("{0}: Open" + vbCrLf, e.sPortName))

            Case IRP_MJ_READ
                dwReadTotal += e.dwSize
                redtData.SelectionColor = Color.Blue
                redtData.AppendText(String.Format("{0}, Read({1:D}): {2}" + vbCrLf, e.sPortName, e.dwSize, e.sData))

            Case IRP_MJ_WRITE
                dwWriteTotal += e.dwSize
                redtData.SelectionColor = Color.Green
                redtData.AppendText(String.Format("{0}, Write({1:D}): {2}" + vbCrLf, e.sPortName, e.dwSize, e.sData))
            Case Else
                If (e.dwCtrlCode > &H400) Then
                    ctlData.AppendText(String.Format("{0}, CTLCode({1:D}): {2}" + vbCrLf, e.sPortName, e.dwCtrlCode, e.sData))
                End If
        End Select


        If (e.dwCtrlCode = IRP_MJ_READ) Or (e.dwCtrlCode = IRP_MJ_WRITE) Then        
            lblTip.Text = String.Format("Write:  {0:D}(Bytes), Read: {1:D}(Bytes)", dwWriteTotal, dwReadTotal)

        End If
    End Sub

    Private Sub AxCommMonitor1_OnMonitor(ByVal sender As System.Object, ByVal e As AxCommMonitor6x.ICommMonitor6Events_OnMonitorEvent) Handles AxCommMonitor1.OnMonitor
        ' this input bin data 
    End Sub
End Class
