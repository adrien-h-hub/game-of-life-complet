# PowerShell script to take screenshots of Game of Life
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

function Take-Screenshot {
    param(
        [string]$FilePath
    )
    
    $screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
    $bitmap = New-Object System.Drawing.Bitmap($screen.Width, $screen.Height)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.CopyFromScreen($screen.Location, [System.Drawing.Point]::Empty, $screen.Size)
    $bitmap.Save($FilePath, [System.Drawing.Imaging.ImageFormat]::Png)
    $graphics.Dispose()
    $bitmap.Dispose()
    Write-Host "Screenshot saved: $FilePath"
}

# Wait for user to position window
Write-Host "=========================================="
Write-Host "SCREENSHOT TOOL FOR GAME OF LIFE"
Write-Host "=========================================="
Write-Host ""
Write-Host "Instructions:"
Write-Host "1. Make sure Game of Life window is visible"
Write-Host "2. Press Enter to take Screenshot 1 (Main Interface)"
Read-Host "Press Enter to continue"

Take-Screenshot -FilePath "screenshots\01_main_interface.png"
Write-Host ""

Write-Host "3. Press R in the game to generate a pattern"
Write-Host "4. Press Enter to take Screenshot 2 (Pattern)"
Read-Host "Press Enter to continue"

Take-Screenshot -FilePath "screenshots\02_pattern.png"
Write-Host ""

Write-Host "5. Press SPACE to start simulation"
Write-Host "6. Wait a few seconds for evolution"
Write-Host "7. Press Enter to take Screenshot 3 (Evolution)"
Read-Host "Press Enter to continue"

Take-Screenshot -FilePath "screenshots\03_evolution.png"
Write-Host ""

Write-Host "8. Press K to change theme"
Write-Host "9. Press Enter to take Screenshot 4 (Theme)"
Read-Host "Press Enter to continue"

Take-Screenshot -FilePath "screenshots\04_theme.png"
Write-Host ""

Write-Host "10. Press H to show help"
Write-Host "11. Press Enter to take Screenshot 5 (Help)"
Read-Host "Press Enter to continue"

Take-Screenshot -FilePath "screenshots\05_help.png"
Write-Host ""

Write-Host "=========================================="
Write-Host "All screenshots captured successfully!"
Write-Host "Check the screenshots folder"
Write-Host "=========================================="
