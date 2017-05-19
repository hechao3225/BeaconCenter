package monitor;

import org.eclipse.swt.SWT;
import org.eclipse.swt.SWTError;
import org.eclipse.swt.ole.win32.OLE;
import org.eclipse.swt.ole.win32.OleAutomation;
import org.eclipse.swt.ole.win32.OleControlSite;
import org.eclipse.swt.ole.win32.OleEvent;
import org.eclipse.swt.ole.win32.OleFrame;
import org.eclipse.swt.ole.win32.OleListener;
import org.eclipse.swt.ole.win32.Variant;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class Monitor extends Shell {

	/**
	 * Launch the application.
	 * @param args
	 */
	
	static  int iTotalRead = 0;
	static  int iTotalWrite = 0;

	static  boolean fActive = false;
	static  boolean fPause = false;
	static Text textData;
	static Text textCtrl;
	static Composite pState;
	//static Label lbTip;
	
	static OleAutomation CommMonitor;

	
	public static void main(String args[]) {
		try {
			Display display = Display.getDefault();
			Monitor shell = new Monitor(display);
			shell.open();
			shell.layout();	
			
			OleControlSite controlSite;
			try {
				OleFrame frame = new OleFrame(shell, SWT.NONE);
				  controlSite = new OleControlSite(frame, SWT.NONE, "CommMonitor6x.CommMonitor");
				controlSite.doVerb(OLE.OLEIVERB_INPLACEACTIVATE);

			} catch (SWTError e) {
				System.out.println("Unable to open activeX control");
				display.dispose();
				return;
			}
			
			CommMonitor = new OleAutomation(controlSite);	
			final Label lbTip = new Label(pState, SWT.NONE);
			lbTip.setBounds(2, 10, 500, 17);
 
			final  int  IRP_MJ_CREATE                   =0x00;
			final  int  IRP_MJ_CLOSE                    =0x02;
			final  int  IRP_MJ_READ                     =0x03;
			final  int  IRP_MJ_WRITE                    =0x04;
			 
			 //ICommMonitor6Events OnMonitor=206  OnAscii   = 207
			// OnMonitor = 206;//二进制数据   
			 int OnAscii   = 207; //ASCII码娄据
			 controlSite.addEventListener(OnAscii, new OleListener() {
					public void handleEvent(OleEvent event) {
						//System.out.println(event.arguments[0].getString());
						 
						String sPort     = "";
						String sData     = "";
						int dwCtrlCode   = 0;
						int dwSize       = 0;
						
						//参数列表					 
						sPort        = event.arguments[0].getString();
						dwCtrlCode   = event.arguments[1].getInt();
						dwSize       = event.arguments[4].getInt();
						
						if (dwSize > 0)
						    sData     = event.arguments[3].getString();
						
						
						String sLine = "";
						switch(dwCtrlCode)
				        {
					    	case IRP_MJ_CLOSE:	sLine = String.format("%s: Close", sPort); 
					    	    break;
					    	case IRP_MJ_CREATE:	sLine = String.format("%s: Open", sPort);
					    		break;
					    	case IRP_MJ_READ:   sLine = String.format("%s, Read(%d): %s", sPort, dwSize, sData);iTotalRead+=dwSize;
					    		break;
					    	case IRP_MJ_WRITE:  sLine = String.format("%s, Write(%d): %s", sPort, dwSize, sData);iTotalWrite+=dwSize;
					    		break;
					    	default: {
					    		if (dwCtrlCode > 0x400)
					    			sLine = sData;    			
					    	    break;
					    	}
				        };	
				        
				        if (dwCtrlCode > 0x400)     
				        	textCtrl.append(sLine+"\r\n");
				        else{
				        	textData.append(sLine+"\r\n");	
				        	String sTip = String.format("Read:%d(Bytes)    |Write:%d(Bytes)", iTotalRead, iTotalWrite);
				        	//System.out.println(sTip);
				        	lbTip.setText(sTip);
				        	
				        }
					}
			 });
		
			
			while (!shell.isDisposed()) {
				if (!display.readAndDispatch()) {
					display.sleep();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the shell.
	 * @param display
	 */
	public Monitor(Display display) {
		super(display, SWT.DIALOG_TRIM);				
		
		Group grpData = new Group(this, SWT.NONE);
		grpData.setText("Data");
		grpData.setBounds(10, 69, 678, 170);
		grpData.setLayout(null);
		
		textData = new Text(grpData, SWT.BORDER | SWT.MULTI);
		textData.setBounds(3, 17, 672, 150);
		
		Group grpCtrlcode = new Group(this, SWT.NONE);
		grpCtrlcode.setText("CtrlCode");
		grpCtrlcode.setBounds(10, 245, 678, 170);
		
		textCtrl = new Text(grpCtrlcode, SWT.BORDER | SWT.MULTI);
		textCtrl.setBounds(10, 20, 658, 140);
		
		pState = new Composite(this, SWT.NONE);
		pState.setBounds(10, 421, 678, 32);
		

		
		Composite composite = new Composite(this, SWT.NONE);
		composite.setBounds(10, 10, 678, 50);
		
		final Combo combo = new Combo(composite, SWT.NONE);
		combo.setItems(new String[] {"COM1", "COM2", "COM3", "COM4", "COM5", "COM6"});
		combo.setBounds(134, 15, 68, 25);
		combo.select(0);
		
		final Button btnOpen = new Button(composite, SWT.NONE);
		btnOpen.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				if (!fActive){			 
					System.out.println("StartMonitor.....");
					String sComPort = combo.getText();
					int[]  ids = CommMonitor.getIDsOfNames(new String[]{"StartMonitor"});		 					
				    Variant[] rgvarg = new Variant[] {new Variant(sComPort)};		    
				    Variant pVarResult = CommMonitor.invoke(ids[0], rgvarg);
				    fActive = pVarResult.getBoolean();
				    
				}else{
					System.out.println("StopMonitor.....");
		     		        int[]  ids = CommMonitor.getIDsOfNames(new String[]{"StopMonitor"});
	     		                CommMonitor.invoke(ids[0]);
	     		                fActive = false;
				}	
				if (fActive )
				  btnOpen.setText ("Stop Monitor");
				else btnOpen.setText ("Start Monitor");
	 	
			}
		});
		btnOpen.setBounds(208, 11, 90, 27);
		btnOpen.setText("Start Monitor");
		
		final Button btnPause = new Button(composite, SWT.NONE);
		btnPause.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				int[]  ids = CommMonitor.getIDsOfNames(new String[]{"PauseMonitor"});	
				Variant[] rgvarg = new Variant[] {new Variant(fPause)};
				Variant pVarResult = CommMonitor.invoke(ids[0], rgvarg);
				if (pVarResult.getBoolean())
				    fPause = !fPause;
				
				if (fPause)					
	    	    	btnPause.setText("Continue");
				else
					btnPause.setText ("Pause");
			}
		});
		btnPause.setBounds(304, 11, 80, 27);
		btnPause.setText("Pause");
		
		Button btnAbout = new Button(composite, SWT.NONE);
		btnAbout.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				int[]  ids = CommMonitor.getIDsOfNames(new String[]{"AboutBox"});
				CommMonitor.invoke(ids[0]); 
			}
		});
		btnAbout.setBounds(600, 13, 68, 27);
		btnAbout.setText("About");
		
		Button btnClear = new Button(composite, SWT.NONE);
		btnClear.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				textCtrl.setText("");
				textData.setText("");
			}
		});
		btnClear.setBounds(10, 15, 80, 27);
		btnClear.setText("Clear");
			
		createContents();
	}

	/**
	 * Create contents of the shell.
	 */
	protected void createContents() {
		setText("CommMonitorx for Java7 SWT Application");
		setSize(704, 481);

	}

	@Override
	protected void checkSubclass() {
		// Disable the check that prevents subclassing of SWT components
	}
}
