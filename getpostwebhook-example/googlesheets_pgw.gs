// Set Global Variables ------------------------------------------------------------------------------
/* 
ACCESS_TOKEN: Go to build.particle.io and click "Settings" on the left side panel
PARTICLE_DEVICE_ID: Identify device ID from the console, or from using "particle list"
SPREADSHEET_ID: Look on the URL for your Google Sheet for the long random string
*/
PropertiesService.getScriptProperties().setProperty('SHEET_NAME', 'Sheet1');
PropertiesService.getScriptProperties().setProperty('PARTICLE_ACCESS_TOKEN', '<enter access token>');
PropertiesService.getScriptProperties().setProperty('PARTICLE_DEVICE_ID', '<enter device id>');
PropertiesService.getScriptProperties().setProperty('SPREADSHEET_ID', '<enter spreadsheetid>');

// ---------------------------------------------------------------------------------------------------



// Handle the webhook using doPost() -------------------------------------------------
function doPost(e){
  
  // Set which spreadsheet to output this data to
  var spreadsheet_id = PropertiesService.getScriptProperties().getProperty('SPREADSHEET_ID');
  var sheet = SpreadsheetApp.openById(spreadsheet_id).getSheetByName( 
    PropertiesService.getScriptProperties().getProperty('SHEET_NAME'));
  
  // Fill the "Webhook Data" cell with the parameters of the webhook package sent
  sheet.getRange("D2").setValue(e.parameter);
  
  return ContentService.createTextOutput(JSON.stringify({text:"webhook received"})).setMimeType(ContentService.MimeType.JSON);;
  
}

// Handle the button click for Post Request -------------------------------------------------
function PostRequest() {
  var spreadsheet_id = SpreadsheetApp.getActiveSpreadsheet().getId();
  var sheet = SpreadsheetApp.openById(spreadsheet_id).getSheetByName( 
    PropertiesService.getScriptProperties().getProperty('SHEET_NAME'));
  
  // API url goes like this:
  // https://api.particle.io/v1/devices/<DEVICEID>/
  // led?args=on&access_token=<ACCESSTOKEN>
  var device_id = PropertiesService.getScriptProperties().getProperty('PARTICLE_DEVICE_ID');
  var access_token = PropertiesService.getScriptProperties().getProperty('PARTICLE_ACCESS_TOKEN');
  var function_name = sheet.getRange("B4").getValue();
  var request = sheet.getRange("B2").getValue();
  var url = "https://api.particle.io/v1/devices/" + device_id + "/" + function_name + "?" + 
    "access_token=" + access_token;

  // Create a form which will be sent as the payload to the post request
  var formData = {
    'args' : request
    
  };
  
  // Create the options
  var options =
      {
        "method"  : "POST", 
        "payload"  : formData,
        "followRedirects" : true,
        "muteHttpExceptions": false
      };
  
  // Send Post request body to the URL indicated
  var result = UrlFetchApp.fetch(url, options);
  
  // Display response in Cell
  if (result.getResponseCode() == 200) {  
    var params = JSON.parse(result.getContentText());
    sheet.getRange("B3").setValue(params);
  }
}

// Handle the button click for Get Request -------------------------------------------------
function GetRequest() {
  // Start by trying in postman
  
  // Set which spreadsheet to pull or output information
  var spreadsheet_id = SpreadsheetApp.getActiveSpreadsheet().getId();
  var sheet = SpreadsheetApp.openById(spreadsheet_id).getSheetByName( 
    PropertiesService.getScriptProperties().getProperty('SHEET_NAME'));
  
  // API url goes like this: 
  // https://api.particle.io/v1/devices/<PARTICLE_DEVICE_ID>/<VARIABLE_NAME>?access_token=<PARTICLE_ACCESS_TOKEN>
  var device_id = PropertiesService.getScriptProperties().getProperty('PARTICLE_DEVICE_ID');
  var access_token = PropertiesService.getScriptProperties().getProperty('PARTICLE_ACCESS_TOKEN');
  var variable_name = sheet.getRange("C2").getValue();
  var url = "https://api.particle.io/v1/devices/" + device_id + "/" + variable_name + "?access_token=" + access_token
  
  // Not sure if all options are necessary
  var options =
      {
        "method"  : "GET",   
        "followRedirects" : true,
        "muteHttpExceptions": true
      };
  
  // Send Get request body to the URL indicated
  var result = UrlFetchApp.fetch(url, options);
  
  // Display response in Cell
  if (result.getResponseCode() == 200) {
    var params = JSON.parse(result.getContentText());
    sheet.getRange("C3").setValue(params);
  };
}
