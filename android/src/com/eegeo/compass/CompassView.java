// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.compass;

import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IRuntimePermissionResultHandler;
import com.eegeo.runtimepermissions.RuntimePermissionDispatcher;
import com.eegeo.ui.IAnimatedView;
import com.eegeo.ui.IViewAnimator;
import com.eegeo.ui.ViewAnimator;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v4.app.ActivityCompat;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;

public class CompassView implements View.OnClickListener, IRuntimePermissionResultHandler, IAnimatedView {
	private MainActivity m_activity = null;
	private long m_nativeCallerPointer;
	private View m_view = null;
	private IViewAnimator m_viewAnimator;
	private View m_compassPoint = null;
	private ImageView m_compassInner = null;
	private View m_compassDefault = null;
	private View m_compassLocked = null;
	private View m_compassUnlocked = null;
	private boolean m_requestedLocationForCompass = false;

	private final long m_stateChangeAnimationTimeMilliseconds = 200;
	private final long RotationHighlightAnimationMilliseconds = 200;
	private final long NeedleLockRotationAnimationMilliseconds = 200;

	private final float CompassOuterShapeInactiveAlpha = 0.5f;
	private final float CompassOuterShapeActiveAlpha = 1.0f;


	public CompassView(MainActivity activity, long nativeCallerPointer) {
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		createView();
	}

	public void destroy() {
		final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
		uiRoot.removeView(m_view);
		m_view = null;
		m_viewAnimator = null;
		m_activity.getRuntimePermissionDispatcher().removeIRuntimePermissionResultHandler(this);
	}

	private void createView() {
		final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.compass_layout, uiRoot, false);
		m_view.setOnClickListener(this);

		m_compassPoint = m_view.findViewById(R.id.compass_arrow_shape);
		m_compassInner = (ImageView) m_view.findViewById(R.id.compass_inner_shape);
		m_compassInner.setVisibility(View.GONE);

		m_compassDefault = m_view.findViewById(R.id.compass_outer_shape);
		m_compassLocked = m_view.findViewById(R.id.compass_new_locked);
		m_compassUnlocked = m_view.findViewById(R.id.compass_new_unlocked);

		m_viewAnimator = new ViewAnimator(this, m_view);

		m_viewAnimator.registerLayoutChangeListener();

		m_activity.getRuntimePermissionDispatcher().addRuntimePermissionResultHandler(this);

		m_compassPoint.setAlpha(CompassOuterShapeInactiveAlpha);
		uiRoot.addView(m_view);
		showGpsDisabledView();
	}

	public void ViewLayoutChanged()
	{
		final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);

		final float screenWidth = uiRoot.getWidth();
		final float screenHeight = uiRoot.getHeight();

		final float viewWidth = m_view.getWidth();
		final float viewHeight = m_view.getHeight();

		m_viewAnimator.setActivePos((screenHeight - viewHeight) - m_activity.dipAsPx(8.f));
		m_viewAnimator.setInactivePos(screenHeight + viewHeight);

		m_view.setX((screenWidth * 0.5f) - (viewWidth * 0.5f));
		m_view.setY(screenHeight + viewHeight);
	}

	public void updateHeading(float headingAngleRadians) {
		final float rotationDegrees = (float) -Math.toDegrees(headingAngleRadians);
		m_compassPoint.setRotation(rotationDegrees);
        m_compassLocked.setRotation(rotationDegrees);
	}

	public void showGpsDisabledView() {
		m_compassInner.setVisibility(View.GONE);
		m_compassDefault.setVisibility(View.VISIBLE);
		m_compassLocked.setVisibility(View.INVISIBLE);
		m_compassUnlocked.setVisibility(View.INVISIBLE);
	}

	public void showGpsFollowView() {
		m_compassLocked.setRotation(m_compassPoint.getRotation());

		m_compassInner.setVisibility(View.VISIBLE);
		m_compassDefault.setVisibility(View.INVISIBLE);
		m_compassLocked.setVisibility(View.VISIBLE);
		m_compassUnlocked.setVisibility(View.INVISIBLE);
	}

	public void showGpsCompassModeView() {
		final float NeedleLockeRotationDegrees = 0.0f;
		m_compassUnlocked.setRotation(m_compassLocked.getRotation());

		m_compassInner.setVisibility(View.VISIBLE);
		m_compassLocked.setVisibility(View.INVISIBLE);
		m_compassUnlocked.setVisibility(View.VISIBLE);
		m_compassDefault.setVisibility(View.INVISIBLE);

		m_compassUnlocked.animate()
				.rotation(NeedleLockeRotationDegrees)
				.setDuration(NeedleLockRotationAnimationMilliseconds);
	}

	public void notifyGpsUnauthorized() {
		AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(m_activity);
		alertDialogBuilder.setTitle("Location Services disabled")
				.setMessage("GPS Compass inaccessable: Location Services are not enabled for this application. You can change this in your device settings.")
				.setCancelable(false)
				.setPositiveButton("Ok", new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				});
		AlertDialog alert = alertDialogBuilder.create();
		alert.show();
	}

	@Override
	public void onClick(View view)
	{
    	if(m_activity.getRuntimePermissionDispatcher().hasLocationPermissions())
    	{
    		CompassViewJniMethods.HandleClick(m_nativeCallerPointer);
    	}
        else
		{
			m_requestedLocationForCompass = true;
		}
    }

    private void createBitMap(Paint.Style style) 
    {
        final int innerDiameter = m_activity.dipAsPx(20);
        Bitmap bmp = Bitmap.createBitmap(innerDiameter, innerDiameter, Bitmap.Config.ARGB_8888);
        Canvas compassInnerCanvas = new Canvas(bmp);
        compassInnerCanvas.drawColor(Color.TRANSPARENT);
        Paint compassInnerPaint = new Paint();
        compassInnerPaint.setStyle(style);
        compassInnerPaint.setColor(m_activity.getResources().getColor(R.color.white));
        compassInnerPaint.setAntiAlias(true);
        compassInnerPaint.setFilterBitmap(true);
        compassInnerCanvas.drawCircle(innerDiameter / 2, innerDiameter/2 , innerDiameter/2, compassInnerPaint);   
        m_compassInner.setImageBitmap(bmp);  
        m_compassInner.invalidate();
    }

	public void animateToActive() {
		m_viewAnimator.animateToActive(m_stateChangeAnimationTimeMilliseconds);
	}

	public void animateToInactive() {
		m_viewAnimator.animateToInactive(m_stateChangeAnimationTimeMilliseconds);
	}

	public void animateToIntermediateOnScreenState(final float onScreenState) {
		m_viewAnimator.animateToOnScreenState(onScreenState);
	}

	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		if (requestCode != RuntimePermissionDispatcher.GPS_PERMISSION_REQUEST_CODE) {
			return;
		}
		if (!m_requestedLocationForCompass) {
			return;
		}
		// If request is cancelled, the result arrays are empty.
		if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
			CompassViewJniMethods.HandleClick(m_nativeCallerPointer);
        } else {
			// If any of the permission is denied, we can't use the camera
			// properly, so we will show the dialog with agree or cancel dialog
			showPermissionRequiredDialog(m_activity);
		}
		return;
	}

	public void setRotationHighlight(boolean shouldShowRotationHighlight) {
		m_compassPoint.animate()
				.alpha(shouldShowRotationHighlight ? CompassOuterShapeActiveAlpha : CompassOuterShapeInactiveAlpha)
				.setDuration(RotationHighlightAnimationMilliseconds);
	}

    private void showPermissionRequiredDialog(final Activity context) 
    {
		DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener()
		{
			@Override
			public void onClick(DialogInterface dialog, int which) 
			{
				dialog.dismiss();
				switch (which)
				{
				case DialogInterface.BUTTON_POSITIVE:
					if(ActivityCompat.shouldShowRequestPermissionRationale(context, Manifest.permission.ACCESS_FINE_LOCATION))
					{
						// Checking Permissions again
						m_activity.getRuntimePermissionDispatcher().hasLocationPermissions();
					}
					else
					{
						// Open App's Settings Page for user to grand permission manually
						m_activity.getRuntimePermissionDispatcher().startAppSettings(context);
					}
					break;
				}
			}
		};

		AlertDialog.Builder builder = new AlertDialog.Builder(context);
		builder.setMessage(context.getResources().getString(R.string.required_location_permission_text))
				.setPositiveButton(context.getResources().getString(R.string.ok_text), dialogClickListener)
				.setNegativeButton(context.getResources().getString(R.string.cancel_text), dialogClickListener).show();
	}
}
