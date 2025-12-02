# Automated Screenshot Tool for Conway's Game of Life
# This script helps capture screenshots automatically with minimal user input

Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  AUTO SCREENSHOT TOOL" -ForegroundColor Cyan
Write-Host "  Conway's Game of Life v1.1.0" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Function to take screenshot
function Take-Screenshot {
    param(
        [string]$FilePath,
        [string]$Description
    )
    
    Write-Host "📸 Taking screenshot: $Description" -ForegroundColor Yellow
    Write-Host "   Saved to: $FilePath" -ForegroundColor Gray
    
    $screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
    $bitmap = New-Object System.Drawing.Bitmap($screen.Width, $screen.Height)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.CopyFromScreen($screen.Location, [System.Drawing.Point]::Empty, $screen.Size)
    
    # Save as PNG
    $bitmap.Save($FilePath, [System.Drawing.Imaging.ImageFormat]::Png)
    
    $graphics.Dispose()
    $bitmap.Dispose()
    
    Write-Host "✅ Screenshot saved!" -ForegroundColor Green
    Write-Host ""
}

# Check if screenshots directory exists
if (-not (Test-Path "screenshots")) {
    New-Item -ItemType Directory -Path "screenshots" | Out-Null
    Write-Host "✅ Created screenshots directory" -ForegroundColor Green
}

Write-Host ""
Write-Host "🎮 INSTRUCTIONS:" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "We will capture 5 screenshots of the Game of Life:" -ForegroundColor White
Write-Host ""
Write-Host "  1️⃣  Main interface (stats panel, grid)" -ForegroundColor Yellow
Write-Host "  2️⃣  Random pattern generated (after pressing R)" -ForegroundColor Yellow
Write-Host "  3️⃣  Pattern evolution (after pressing SPACE)" -ForegroundColor Yellow
Write-Host "  4️⃣  Different theme (after pressing K)" -ForegroundColor Yellow
Write-Host "  5️⃣  Help overlay (after pressing H)" -ForegroundColor Yellow
Write-Host ""
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""

# Check if Game of Life is running
Write-Host "🔍 Checking if Game of Life is running..." -ForegroundColor Yellow
$gameProcess = Get-Process -Name "GameOfLife" -ErrorAction SilentlyContinue

if (-not $gameProcess) {
    Write-Host "⚠️  Game of Life is not running!" -ForegroundColor Yellow
    Write-Host ""
    $launch = Read-Host "Do you want to launch it now? (Y/n)"
    
    if ($launch -ne "n" -and $launch -ne "N") {
        $gamePath = "..\..\GameOfLife_App\GameOfLife.exe"
        if (Test-Path $gamePath) {
            Start-Process -FilePath $gamePath -WorkingDirectory "..\..\GameOfLife_App"
            Write-Host "✅ Game launched! Waiting 3 seconds..." -ForegroundColor Green
            Start-Sleep -Seconds 3
        } else {
            Write-Host "❌ GameOfLife.exe not found at: $gamePath" -ForegroundColor Red
            Write-Host "Please launch the game manually and run this script again." -ForegroundColor Red
            exit 1
        }
    } else {
        Write-Host "Please launch Game of Life and run this script again." -ForegroundColor Red
        exit 1
    }
}

Write-Host "✅ Game of Life is running!" -ForegroundColor Green
Write-Host ""

# Screenshot 1: Main Interface
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Screenshot 1/5: Main Interface" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Make sure the Game of Life window is visible." -ForegroundColor White
Write-Host "This will capture the main interface with stats panel." -ForegroundColor Gray
Write-Host ""
Read-Host "Press ENTER when ready"
Take-Screenshot -FilePath "screenshots\01_main_interface.png" -Description "Main Interface"
Start-Sleep -Seconds 1

# Screenshot 2: Pattern Generated
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Screenshot 2/5: Random Pattern" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "ACTION REQUIRED:" -ForegroundColor Yellow
Write-Host "1. Click on the Game of Life window" -ForegroundColor White
Write-Host "2. Press R key to generate a random pattern" -ForegroundColor White
Write-Host "3. Make sure the pattern is visible in the center" -ForegroundColor White
Write-Host ""
Read-Host "Press ENTER after pressing R"
Take-Screenshot -FilePath "screenshots\02_pattern.png" -Description "Random Pattern Generated"
Start-Sleep -Seconds 1

# Screenshot 3: Evolution
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Screenshot 3/5: Pattern Evolution" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "ACTION REQUIRED:" -ForegroundColor Yellow
Write-Host "1. Press SPACE to start the simulation" -ForegroundColor White
Write-Host "2. Wait about 5-10 seconds for interesting evolution" -ForegroundColor White
Write-Host "3. The pattern should be evolving on screen" -ForegroundColor White
Write-Host ""
Read-Host "Press ENTER when evolution is visible"
Take-Screenshot -FilePath "screenshots\03_evolution.png" -Description "Pattern Evolution"
Start-Sleep -Seconds 1

# Screenshot 4: Different Theme
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Screenshot 4/5: Color Theme" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "ACTION REQUIRED:" -ForegroundColor Yellow
Write-Host "1. Press K to change the color theme" -ForegroundColor White
Write-Host "2. Press K multiple times to find a nice theme" -ForegroundColor White
Write-Host "   (Try Ocean, Forest, or Sunset themes)" -ForegroundColor Gray
Write-Host "3. Make sure the new theme is clearly visible" -ForegroundColor White
Write-Host ""
Read-Host "Press ENTER when you have a good theme"
Take-Screenshot -FilePath "screenshots\04_theme.png" -Description "Different Theme"
Start-Sleep -Seconds 1

# Screenshot 5: Help Overlay
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Screenshot 5/5: Help Overlay" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "ACTION REQUIRED:" -ForegroundColor Yellow
Write-Host "1. Press H to show the help overlay" -ForegroundColor White
Write-Host "2. Make sure all controls are visible" -ForegroundColor White
Write-Host ""
Read-Host "Press ENTER after pressing H"
Take-Screenshot -FilePath "screenshots\05_help.png" -Description "Help Overlay"

# Summary
Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "✅ ALL SCREENSHOTS CAPTURED!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# List captured screenshots
Write-Host "📁 Captured Screenshots:" -ForegroundColor Cyan
Get-ChildItem -Path "screenshots\*.png" | ForEach-Object {
    $size = [math]::Round($_.Length / 1KB, 2)
    Write-Host "   ✓ $($_.Name) ($size KB)" -ForegroundColor Green
}

Write-Host ""
Write-Host "📸 Screenshots saved to: screenshots\" -ForegroundColor Yellow
Write-Host ""

# Optional: Open folder
$openFolder = Read-Host "Do you want to open the screenshots folder? (Y/n)"
if ($openFolder -ne "n" -and $openFolder -ne "N") {
    Invoke-Item "screenshots"
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Next steps:" -ForegroundColor Cyan
Write-Host "1. Review screenshots in screenshots/ folder" -ForegroundColor White
Write-Host "2. Retake any if needed by running this script again" -ForegroundColor White
Write-Host "3. Add to Git: git add screenshots/" -ForegroundColor White
Write-Host "4. Build installer with Inno Setup" -ForegroundColor White
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

Write-Host "Press any key to exit" -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')
