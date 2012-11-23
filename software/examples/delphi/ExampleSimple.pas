program ExampleSimple;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletIndustrialDigitalOut4;

type
  TExample = class
  private
    ipcon: TIPConnection;
    ido4: TBrickletIndustrialDigitalOut4;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'xyz'; { Change to your UID }

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  ido4 := TBrickletIndustrialDigitalOut4.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(ido4);
  { Don't use device before it is added to a connection }

  { Turn pins 0, 3 high and pins 1, 2 low. }
  ido4.SetValue((1 shl 0) or (1 shl 3));

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
